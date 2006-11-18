<?xml version="1.0" encoding="utf-8"?>

<!--
	Provides a template to create a menu for the XHTML pages.

	The menu contains a link to each section of the site except for the current page,
	which uses a simple paragraph. All those elements are created in an unordered list.
	The menu entries are specified in "menu.xml" file.
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:page="http://lusi.berlios.de/namespaces/page"
		xmlns:menu="http://lusi.berlios.de/namespaces/menu" xmlns="http://www.w3.org/1999/xhtml">

	<!--
		Creates the menu for the pages.
		The menu is got from an external XML document. This document, called menu.xml, contains
		the menu as an unordered list of links to the different pages.
		This list and its elements is copied, except for the link to the current page, which is
		substituted by a paragraph with the content of the link (also inline elements).
	-->
	<xsl:template name="menu">
		<xsl:comment> Menu </xsl:comment>
		<div id="menu">
			<ul>
			
			<xsl:variable name="pageId" select="/page:page/page:variables/page:pageId"/>
			
			<xsl:for-each select="document('menu.xml')/menu:menu/xhtml:li" xmlns:menu="http://lusi.berlios.de/namespaces/menu" xmlns:xhtml="http://www.w3.org/1999/xhtml">
				<xsl:choose>
					<xsl:when test="* = $pageId">
						<li>
							<p>
								<xsl:apply-templates select="xhtml:a[. = $pageId]/text() | xhtml:a/*[node() = $pageId]"/>
							</p>
						</li>
					</xsl:when>
					<xsl:otherwise>
						<xsl:apply-templates select="."/>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:for-each>
	
			</ul>
		</div>
	</xsl:template>

	<!--
		Matches all the menu child elements.
		Menu child elements are XHTML elements. They're copied directly to the output,
		removing the namespace declaration.
		xsl:copy-of also copies the result fragment tree to the output, but it keeps all
		the namespaces, even XML-Schema Instance ones, so the output is poluted.
	-->
	<xsl:template match="menu:menu//*">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates/>
		</xsl:copy>
	</xsl:template>
	
	<!--
		Copies an attribute if anyone more specific wasn't matched.
	-->
	<xsl:template match="menu:menu//@*">
		<xsl:copy-of select="."/>
	</xsl:template>

</xsl:stylesheet>