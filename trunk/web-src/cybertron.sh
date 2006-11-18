#!/bin/bash
#
# This script creates the website from the XML documents and data dirs.
# It can be invoked with -e, -o and -u options.
# -e is the output XHTML files encoding to be used. Default is utf-8.
# -o is the output directory to be used. Default is "../build/"
# -u is the base URL where the website will be.
#
# It needs xsltproc, xmllint (with support for XML Schema) and, if other
# encoding than utf-8 is used, recode.
#
# Cybertron name was used as an easter egg for Transformers animation series,
# as Cybertron was the planet where all the Transformers lived... This script
# prepares everything needed by the XSL "Transformers" and creates and
# environment to be executed... so that's why it's called cybertron :)
#
# TODO
# -create XHTML files only when they were changed since the last execution.
# -change this script into a Makefile?


# Validates all the XML files under pages directory using XML Schema.
# The XML Schema is located at pages/page.xsd
function validateXmlPages() {
	returnValue=0;

	for i in `find pages -iname "*.xml"`
	do
		xmllint --noout --schema pages/page.xsd $i;
		let "returnValue = $returnValue || $?";
	done

	return $returnValue;
}

# Validates the XML newsList.xml file using XML Schema.
# The XML Schema is located at newsList.xsd
function validateNews() {
	xmllint --noout --schema newsList.xsd newsList.xml;
	return $?;
}

# Validates the XML screenshotsList.xml file using DTD.
# The DTD is located at screenshotsList.dtd
function validateScreenshotsList() {
	xmllint --noout --valid screenshotsList.xml \
		&& echo "screenshotsList.xml validates";
	return $?;
}

# Validates all the XML files which have a DTD oir XML Schema.
# Those files are pages files, news file and screenshotsList file.
function validate() {
	validation=0;
	
	validateXmlPages;
	let "validation = $validation || $?";
	
	validateNews;
	let "validation = $validation || $?";
	
	validateScreenshotsList;
	let "validation = $validation || $?";
	
	return $validation;
}

# Prepares the XML pages that need to be updated before transforming them to
# XHTML.
# The pages that needs update are index.xml, news.xml and screenshots.xml The
# first two have their news list updated, and the last its screenshots list.
function preparePages() {
	xsltproc -o $newsHtmlTmpFile news-toHTML.xsl newsList.xml;

	# Prepares index.xml
	xsltproc --stringparam newsHtmlFile $newsHtmlTmpFile -o pages/index.xml \
		updateNewsInPage.xsl pages/index.xml
	xmllint --format -o pages/index.xml pages/index.xml;
	
	# Prepares news.xml
	xsltproc --stringparam newsHtmlFile $newsHtmlTmpFile \
		--stringparam numberOfNews -1 -o pages/news.xml \
		updateNewsInPage.xsl pages/news.xml
	xmllint --format -o pages/news.xml pages/news.xml;
	
	# Prepares screenshots.xml
	xsltproc --stringparam screenshotsHtmlFile screenshotsList.xml \
		-o pages/screenshots.xml updateScreenshotsInPage.xsl \
		pages/screenshots.xml
	xmllint --format -o pages/screenshots.xml pages/screenshots.xml;
}

# Transforms all the XML documents under pages directory.
# It creates all the XHTML pages using optimusPrime XSLT.
# The pages are copied to the output dir (using subdirectories if they
# existed under pages directory) and also reformatted (because xsltproc
# sometimes doesn't create well formatted documents).
# Before creating the XHTML pages, the output directory is created if it
# doesn't exist. If it isn't valid, it returns 1.
function createPages() {
	if [ ! -e $outputDir ]; then
		mkdir -p $outputDir;
		if [ $? -ne 0 ]; then
			return 1;
		fi
	fi

	cd pages;

	for i in `find . -iname "*.xml"`
	do
		# Gets the extension of the file
		fileExtension=`expr match "$i" '.*\(\.[^\.]**\)'`;
		# Removes the extension of the file from the file name
		fileName=${i%"$fileExtension"}
		# Removes leading "./" from the file name
		fileName=${fileName:2};

		xsltproc -o ../$outputDir/$fileName.html ../transformers/optimusPrime.xsl $fileName.xml;
	
		xmllint --format -o ../$outputDir/$fileName.html ../$outputDir/$fileName.html;

		if [ $encoding != "utf-8" ]; then
			recode utf-8..$encoding ../$outputDir/$fileName.html;
			sed -e "s/utf-8/$encoding/g" ../$outputDir/$fileName.html > ../$outputDir/$fileName.html.tmp;
			mv ../$outputDir/$fileName.html.tmp ../$outputDir/$fileName.html
		fi
	done
	
	cd ..;

	return 0;
}

# Creates the news feed from newsList.xml
# The feed is copied to "feed/atom/news.xml" under output dir.
function createFeeds() {
	xsltproc --stringparam baseURL $baseURL -o $outputDir/feed/atom/news.xml news-toAtom.xsl newsList.xml;
}

# Copies the data dirs to the output dir.
function copyDataDirs() {
	cp -r data/* $outputDir;
}

# Copies the source dir to the output dir.
function copySrcDir() {
	cp -r . $outputDir/src;
}

# Packs the source dir and copies it to the files subdirectory of output dir.
function packSrcDir() {
	tar -czf $outputDir/files/webSrc.tar.gz ../src;
}


encoding="utf-8";
outputDir=../build/;
baseURL="http://lusi.berlios.de/";

while getopts e:o:u: o
do
	case "$o" in
	e)	encoding="$OPTARG";;
	o)	outputDir="$OPTARG";;
	u)	baseURL="$OPTARG";;
	[?])	echo "Usage: $0 [-e encoding] [-o outputDir] [-u baseURL]";
		echo "	Default encoding: utf-8";
		echo "	Default output directory: ../build/";
		echo "	Default baseURL: http://lusi.berlios.de/";
		exit 1;;
	esac
done
shift $(($OPTIND -1))

# Ensures baseURL ends with a "/"
if [ ${baseURL:`expr ${#baseURL} - 1`} != "/" ]; then
	baseURL=$baseURL"/";
fi

export XMLLINT_INDENT="	";

newsHtmlTmpFile=news-html.xml;


echo "Validating XML files..."
validate;
if [ $? -ne 0 ]; then
	echo "Validation failed. Aborting...";
	exit;
fi

echo "Preparing pages...";
preparePages;

echo "Creating XHTML pages...";
createPages;
if [ $? -ne 0 ]; then
	echo "Output directory $outputDir isn't valid. Aborting..."
	exit;
fi

echo "Creating feeds...";
createFeeds;

echo "Copying data dirs...";
copyDataDirs;

if [ $outputDir != .. ]; then
	echo "Copying source dir...";
	copySrcDir;
fi;

echo "Packing source dir...";
packSrcDir;

echo "Cleaning up...";
rm -f $newsHtmlTmpFile;

echo "Done!";
