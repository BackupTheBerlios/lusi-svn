<?xml version="1.0" encoding="utf-8"?>

<!--
	Updates the screenshots from a specified file in the XHTML document.
	
	The document must contain a <ul id="screenshotsList"> element. This element
	will be substituted by this same element got from the XHTML screenshosts file.
	The document where the screenshot list is got from must conform to screenshotsList.dtd
	
	All the other elements in the document are copied literally to the output.
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	
	<xsl:output method="xml" encoding="utf-8" indent="yes"/>
	
	<!--
		The path and name of the file containing the screenshots in HTML
		to use in the update.
	-->
	<xsl:param name="screenshotsHtmlFile" select="'screenshotsList.xml'"/>

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
		Copies an ul element, or substitutes it with the screenshots from the HTML
		screenshots file, depending on its id.
		If the id of the ul is equal to "screenshotsList", the ul is substituted by
		the same element in the HTML screenshots file.
		Otherwise, the ul and its children are copied to the output literally
		(if they aren't matched by any specific template other than the "*"
		one. If they're matched, they're processed and the output of the templates
		is used).
	-->
	<xsl:template match="xhtml:ul" xmlns:xhtml="http://www.w3.org/1999/xhtml">
		<xsl:choose>
			<xsl:when test="@id = 'screenshotsList'">
				<xsl:copy>
					<xsl:apply-templates select="@*"/>
					<xsl:copy-of select="document($screenshotsHtmlFile)/xhtml:ul/*"/>
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
