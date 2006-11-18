<?xml version="1.0" encoding="utf-8"?>

<!--
	Main transformer for the XML pages.
	It matches the main element in pages and creates the full XHTML document, containing
	the head and the body with the header, the menu, the content and the footer.
	This is the XSLT to be invoked with XML pages.
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:page="http://lusi.berlios.de/namespaces/page"
		xmlns="http://www.w3.org/1999/xhtml" exclude-result-prefixes="page">

	<xsl:import href="head.xsl"/>
	<xsl:import href="header.xsl"/>
	<xsl:import href="menu.xsl"/>
	<xsl:import href="footer.xsl"/>

	<xsl:output method="xml" encoding="utf-8" indent="yes" doctype-public="-//W3C//DTD XHTML 1.1//EN" doctype-system="http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd"/>

	<!--
		Creates the XHTML document.
		Uses the imported stylesheets for the head element, and the header, the menu and
		the footer in the body.
		The contents are got from the XML document and copied literally to the output (removing
		namespace declarations).
	-->
	<xsl:template match="page:page">
		<html xml:lang="en">

			<xsl:call-template name="head"/>
			<body>
				<div id="wrap">
					<xsl:call-template name="header"/>
					<xsl:call-template name="menu"/>
					<xsl:apply-templates select="page:content"/>
					<xsl:call-template name="footer"/>
				</div>
			</body>
		</html>
	</xsl:template>

	<!--
		Creates the content of the page.
		Content is got form the XML document and copied literally to the output (removing
		namespace declarations).
	-->
	<xsl:template match="page:content">
		<xsl:comment> Content </xsl:comment>
		<xsl:element name="div">
			<xsl:attribute name="id">content</xsl:attribute>
			<xsl:apply-templates select="*"/>
		</xsl:element>
	</xsl:template>

	<!--
		Matches all the content child elements.
		Content child elements are XHTML elements. They're copied directly to the output,
		removing the namespace declaration.
		xsl:copy-of also copies the result fragment tree to the output, but it keeps all
		the namespaces, even XML-Schema Instance ones, so the output is poluted.
	-->
	<xsl:template match="page:content//*">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates/>
		</xsl:copy>
	</xsl:template>
	
	<!--
		Copies an attribute if anyone more specific wasn't matched.
	-->
	<xsl:template match="page:content//@*">
		<xsl:copy-of select="."/>
	</xsl:template>

</xsl:stylesheet>
