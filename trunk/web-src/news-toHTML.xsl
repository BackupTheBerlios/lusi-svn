<?xml version="1.0" encoding="utf-8"?>

<!--
	Creates the XHTML representation of an XML document containing news with a
	specific structure (specified in newsList.xsd).
	
	The XHTML representation created is only a fragment, not a complete XHTML
	document.
	
	The XML input document contains the news in chronological order. The XHTML
	representation should have them in reverse chronological order (newest first),
	so they're reversed. All the news are outputted.

	Each new is identified by its number in the full list of news (indexed in 1).
	An anchor with the number of the new is created in the new title so they can
	be referenced.

	Date and time in XML input document follow RFC 3339, a subset of ISO 8601.
	The time in the XML input document, if present, is slightly processed to a
	friendlier text representation.
	The processed time only contains the hours and minutes. Seconds and time
	zone are ignored, as these news don't really need such information and can
	be omitted (news are likely to happen once in a week or less, so time zone
	and seconds are irrelevant. In fact, even hours and minutes also are).

	The summary in the input XML document contains XHTML code which is outputted
	literally to the content of the new.
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:news="http://lusi.berlios.de/namespaces/news"
		xmlns="http://www.w3.org/1999/xhtml" exclude-result-prefixes="news">
	
	<xsl:output method="xml" encoding="utf-8" indent="yes"/>

	<!--
		Creates a div element containing all the news.
		News are sorted in inverse chronological order (newest first).
	-->
	<xsl:template match="/news:news">
		<div id="news">
			<xsl:apply-templates select="news:new">
				<xsl:sort order="ascending"/>
			</xsl:apply-templates>
		</div>
	</xsl:template>
	
	<!--
		Creates a fragment of a complete XHTML document containing all the news.
		News representation include the title, the last updated date and the
		summary of the new.
		
		Title contains an anchor with "newId(numberOfNew)".
		The date is set to a friendlier version of RFC 3339.
		Summary is copied literally (without namespaces), as it's already in XHTML
		in the input document.

		News are matched in ascending order (thus chronologically inverse),
		so the id of the new is its inverse position (indexed at 1).
	-->
	<xsl:template match="news:new">
		<div class="new">
			<h2 class="newTitle">
				<xsl:element name="a">
					<xsl:attribute name="id">
						<xsl:value-of select="concat('newId', last()-position()+1)"/>
					</xsl:attribute>
					<xsl:attribute name="class">
						<xsl:text>anchorLink</xsl:text>
					</xsl:attribute>
					
					<xsl:value-of select="news:title"/>
				</xsl:element>
			</h2>
			<div class="newBody">
				<p class="newDate">
					<xsl:call-template name="getXHTMLFullDate">
						<xsl:with-param name="fullDate" select="news:fullDate"/>
					</xsl:call-template>
				</p>
				<div class="newContent">
					<xsl:apply-templates select="news:summary/*"/>
				</div>
			</div>
		</div>
	</xsl:template>

	<!--
		Matches all the summary child elements.
		Summary child elements are XHTML elements. They're copied directly to the output,
		removing the namespace declaration.
		xsl:copy-of also copies the result fragment tree to the output, but it keeps all
		the namespaces, even XML-Schema Instance ones, so the output is poluted.
	-->
	<xsl:template match="news:summary//*">
		<xsl:copy>
			<xsl:apply-templates select="@*"/>
			<xsl:apply-templates/>
		</xsl:copy>
	</xsl:template>
	
	<!--
		Matches all the summary and children attributes.
		Copies the attribute if the select expression
		didn't match any more specific
	-->
	<xsl:template match="news:summary//@*">
		<xsl:copy-of select="."/>
	</xsl:template>

	<!--
		Returns the XHTML version of a full date (date and time).
		The fullDate must contain a date and, optionally, a time.
		If present, date or date and time are assumed to follow RFC 3339 (not
		including the separation 'T' between them).
		If present, the time is converted to a more friendlier version. If not,
		only date is outputted.
		
		@param fullDate The full date to convert.
	-->
	<xsl:template name="getXHTMLFullDate">
		<xsl:param name="fullDate"/>

		<xsl:choose>
			<xsl:when test="$fullDate/news:time != ''">
				<xsl:value-of select="concat($fullDate/news:date, ', ')"/>
				<xsl:call-template name="getXHTMLTime">
					<xsl:with-param name="time" select="$fullDate/news:time"/>
				</xsl:call-template>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="$fullDate/news:date"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	
	<!--
		Returns a friendlier version for the RFC 3339 time.
		The returned time only contains the hours and minutes.
		
		@param time The RFC 3339 time to convert.
	-->
	<xsl:template name="getXHTMLTime">
		<xsl:param name="time"/>
		
		<xsl:value-of select="substring($time, 1, 5)"/>
	</xsl:template>
</xsl:stylesheet>
