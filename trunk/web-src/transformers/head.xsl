<?xml version="1.0" encoding="utf-8"?>

<!--
	Provides a template to create the head element for the XHTML pages.
	
	Head element contains meta elements, links and scripts. Through variables,
	new links and scripts can be added, and also script calls in Window.onLoad
	event.
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:page="http://lusi.berlios.de/namespaces/page"
		xmlns="http://www.w3.org/1999/xhtml">

	<!--
		Creates the head element.
		It contains the title of the page, link to the stylesheet, meta elements and
		scripts to round corners.
		New links and scripts can be added with headElements variable in the XML input
		document. Also, scriptOnLoad variable content, if any, is added to the onLoad
		event, before round corners calls are made.
	-->
	<xsl:template name="head">
		<head>
			<xsl:apply-templates select="/page:page/page:variables/page:pageId"/>
			
			<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
			<meta name="language" content="en"/>
			<link rel="stylesheet" type="text/css" href="style/style.css"/>
			<script src="script/roundedCorners.js" type="text/javascript">/*Empty*/</script>
			<script type="text/javascript">
<xsl:comment>
// Hiding the script to old browsers
window.onload = function() {
<xsl:if test="/page:page/page:variables/page:scriptOnLoad != ''">
	<xsl:value-of select="/page:page/page:variables/page:scriptOnLoad"/>
</xsl:if>
roundCorners("#logo", "all");
roundCorners("#wrap", "bottom");
roundCorners(".h2Rounded h2", "all");
roundCorners(".newTitle", "top");
roundCorners(".newBody", "bottom");
}
// Hiding ends </xsl:comment>
			</script>
			
			<xsl:apply-templates select="/page:page/page:variables/page:headElements/*"/>
		</head>
	</xsl:template>
	
	<!--
		Creates the title of the page.
		The title is set to "LUSI: " followed by the pageId.
	-->
	<xsl:template match="page:pageId">
		<xsl:element name="title">
			<xsl:text>LUSI: </xsl:text>
			<xsl:value-of select="."/>
		</xsl:element>
	</xsl:template>

	<!--
		Matches all the headElements child elements.
		Head elements child elements are XHTML elements. They're copied directly to the output,
		removing the namespace declaration.
		xsl:copy-of also copies the result fragment tree to the output, but it keeps all
		the namespaces, even XML-Schema Instance ones, so the output is poluted.
	-->
	<xsl:template match="page:headElements//*">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates/>
		</xsl:copy>
	</xsl:template>
	
	<!--
		Copies an attribute if anyone more specific wasn't matched.
	-->
	<xsl:template match="page:headElements//@*">
		<xsl:copy-of select="."/>
	</xsl:template>

</xsl:stylesheet>
