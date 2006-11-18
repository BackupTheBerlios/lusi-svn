<?xml version="1.0" encoding="utf-8"?>

<!--
	Provides a template to create a header for the XHTML pages.

	It contains project logo.
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns="http://www.w3.org/1999/xhtml">

	<!--
		Creates the header of the pages.
		The header is the first thing added to the body element of the XHTML page.
		It contains project logo.
	-->
	<xsl:template name="header">
		<xsl:comment> Header </xsl:comment>
		<div id="header">
			<div id="logo">
				<div id="logoAcronym">
					<a href="http://developer.berlios.de/projects/lusi/" title="LUSI project page">LUSI</a>
				</div>
				<p id="logoCompleteName">Library for Sourcecode Install</p>
			</div>
		</div>
	</xsl:template>

</xsl:stylesheet>