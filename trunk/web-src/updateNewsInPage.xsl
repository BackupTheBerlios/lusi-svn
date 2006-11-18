<?xml version="1.0" encoding="utf-8"?>

<!--
	Updates the news from a specified file in the XHTML document.
	
	The document must contain a <div id="news"> element. This element
	will be substituted by this same element got from the HTML news file
	and the specified number of news will be appended as children from it.
	
	All the other elements in the document are copied literally to the output.
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:output method="xml" encoding="utf-8" indent="yes"/>
	
	<!--
		The number of the news to be shown in the page.
		If all the news must be shown, use -1.
	-->
	<xsl:param name="numberOfNews" select="'10'"/>

	<!--
		The path and name of the file containing the news in HTML
		to use in the update.
	-->
	<xsl:param name="newsHtmlFile" select="'news-html.xml'"/>

	<!--
		Matches every element and copies it literally to the output,
		including attributes and child nodes.
		The attributes and child nodes are copied also literally
		if no template matches them. If any template matches them,
		the output from the specific template is used.
	-->
	<xsl:template match="*">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates/>
		</xsl:copy>
	</xsl:template>

	<!--
		Copies an attribute if the select expression
		didn't match any more specific
	-->
	<xsl:template match="@*">
		<xsl:copy-of select="."/>
	</xsl:template>

	<!--
		Copies a div element, or substitutes it with the news from the HTML
		news file, depending on its id.
		If the id of the div is equal to "news", the div is substituted by
		the same element in the HTML news file and the specified number of
		child news. -1 denotes all the news.
		Otherwise, the div and its children are copied to the output literally
		(if they aren't matched by any specific template other than the "*"
		one. If they're matched, they're processed and the output of the templates
		is used).
	-->
	<xsl:template match="xhtml:div" xmlns:xhtml="http://www.w3.org/1999/xhtml">
		<xsl:choose>
			<xsl:when test="@id = 'news'">
				<xsl:copy>
					<xsl:apply-templates select="@*"/>
					<xsl:choose>
						<xsl:when test="$numberOfNews = '-1'">
							<xsl:copy-of select="document($newsHtmlFile)/xhtml:div/xhtml:div[@class='new']"/>
						</xsl:when>
						<xsl:otherwise>
							<xsl:copy-of select="document($newsHtmlFile)/xhtml:div/xhtml:div[@class='new' and position() &lt;= $numberOfNews]"/>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:copy>
			</xsl:when>
			<xsl:otherwise>
				<xsl:copy>
					<xsl:apply-templates select="@*"/>
					<xsl:apply-templates/>
				</xsl:copy>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
</xsl:stylesheet>
