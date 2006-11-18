<?xml version="1.0" encoding="utf-8"?>

<!--
	Provides a template to create a footer for the XHTML pages.

	Footer contains validation buttons and BerliOS logo.
	Different validation buttons can also be added using variable "validationButtons"
	in the XML input document.
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:page="http://lusi.berlios.de/namespaces/page"
		xmlns="http://www.w3.org/1999/xhtml">

	<!--
		Creates the footer of the page, containing validation buttons and BerliOS logo.
		Different validation buttons can also be added using variable "validationButtons"
		in the XML page.
		The validation buttons to add must follow the same structure as the validation buttons
		below: a paragraph containing the link to the validation service (or information about
		the button, like in WAI-AAA button) containing the image of the button.
	-->
	<xsl:template name="footer">
		<xsl:comment> Footer </xsl:comment>
		<div id="footer">
			<div id="validation">
				<p>
					<a href="http://validator.w3.org/check?uri=referer" title="Check XHTML">
						<img src="images/valid-xhtml11.png" alt="Valid XHTML 1.1!" height="15" width="80"/>
					</a>
				</p>
				<p>
					<a href="http://jigsaw.w3.org/css-validator/check/referer" title="Check CSS">
						<img src="images/valid-css.png" alt="Valid CSS 2!" height="15" width="80"/>
					</a>
				</p>
				<p>
					<a href="http://www.w3.org/WAI/WCAG1AAA-Conformance" title="Explanation of Level Triple-A Conformance">
						<img src="images/valid-aaa.png" alt="Level Triple-A conformance icon, W3C-WAI Web Content Accessibility Guidelines 1.0" height="15" width="80"/>
					</a>
				</p>
				
				<xsl:apply-templates select="/page:page/page:variables/page:validationButtons/*"/>
				
			</div>
			<div id="logoBerliOS">
				<p>
					<a href="http://developer.berlios.de" title="BerliOS Developer">
<!-- 						<img src="http://developer.berlios.de/bslogo.php?group_id=6496" width="124" height="32" alt="BerliOS Developer Logo"/> -->
						<img src="images/berlios.png" width="124" height="32" alt="BerliOS Developer Logo"/>
					</a>
				</p>
			</div>
		</div>
	</xsl:template>

	<!--
		Matches all the validationButtons child elements.
		Validation buttons child elements are XHTML elements. They're copied directly to the output,
		removing the namespace declaration.
		xsl:copy-of also copies the result fragment tree to the output, but it keeps all
		the namespaces, even XML-Schema Instance ones, so the output is poluted.
	-->
	<xsl:template match="page:validationButtons//*">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates/>
		</xsl:copy>
	</xsl:template>
	
	<!--
		Copies an attribute if anyone more specific wasn't matched.
	-->
	<xsl:template match="page:validationButtons//@*">
		<xsl:copy-of select="."/>
	</xsl:template>

</xsl:stylesheet>