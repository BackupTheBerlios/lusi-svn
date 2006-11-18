<?xml version="1.0" encoding="utf-8"?>

<!--
	Creates an Atom feed from an XML document containing news with a
	specific structure (specified in newsList.xsd).

	The feed is linked to itself and its HTML version. To do that,
	the base URL, the relative feed URL and the relative news page URL
	can be set. They're also used to link the news, and references in the
	summary of the news.
	
	The last updated date of the feed is set, obviously, to the date of the
	newest new.
	
	The XML Document contains the news in chronological order. The feed
	should have them in reverse chronological order (newest news first),
	so they're reversed. The number of news in the feed can be set with
	"numberOfNews" param.

	Each new is identified by its number in the full list of news (indexed in 1).
	Links to the HTML version of the new are created using the news page and an
	anchor with the number of the new.

	Dates in Atom feeds must follow RFC 3339, a subset of ISO 8601. The
	dates in the XML Document are slightly processed to follow that
	specification (a default time is added if only date is found).
	If date or date and time are present, they're expected to follow
	RFC 3339 per se.
	
	The summary in the input XML Document contains XHTML code, so links
	can also be added. These links are processed so, if they're relative,
	the base URL is prefixed to them.
-->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:news="http://lusi.berlios.de/namespaces/news"
		xmlns="http://www.w3.org/2005/Atom" exclude-result-prefixes="news">
	
	<xsl:output method="xml" encoding="utf-8" indent="yes"/>
	
	<!--
		The base URL of the feed site. Must include ending slash.
	-->
	<xsl:param name="baseURL" select="'http://lusi.berlios.de/'"/>
	
	<!--
		The URL to the HTML news page from the base URL.
	-->
	<xsl:param name="newsPageURL" select="'index.html'"/>
	
	<!--
		The URL to the feed from the base URL.
	-->
	<xsl:param name="feedURL" select="'feed/atom/news.xml'"/>

	<!--
		The number of the news to be shown in the feed.
	-->
	<xsl:param name="numberOfNews" select="'10'"/>

	<!--
		Default time to be used if time isn't present in a date.
	-->
	<xsl:param name="defaultTime" select="'00:00:00Z'"/>

	<!--
		Creates a header comment and the feed element (calling the
		metadata and entries templates).
	-->
	<xsl:template match="/news:news">
		<xsl:call-template name="headerComment"/>

		<feed>
			<xsl:call-template name="feedMetadata"/>
			
			<xsl:call-template name="feedEntries"/>
		</feed>
	</xsl:template>
	
	<!--
		Creates a header comment for the feed, before the root element.
	-->
	<xsl:template name="headerComment">
<xsl:comment>

Atom feed for LUSI news.

If you don't know what Atom is, you shouldn't be here :)
However, you may want to learn more about Atom.
If that's the case, ask Wikipedia!:
http://en.wikipedia.org/wiki/Atom_%28standard%29

</xsl:comment>
	</xsl:template>

	<!--
		Creates the metadata elements for the feed.
		It includes title, subtitle, links, updating date, author and id.
		Links are set to the self feed and the HTML version.
		Updating date is get from the date of the last new.
		Id is set to the url to the HTML version of the feed.
	-->
	<xsl:template name="feedMetadata">
		<title>LUSI News</title>
		<subtitle>Atom feed for LUSI project news</subtitle>
		<xsl:element name="link">
			<xsl:attribute name="href">
				<xsl:value-of select="concat($baseURL, $feedURL)"/>
			</xsl:attribute>
			<xsl:attribute name="rel">self</xsl:attribute>
			<xsl:attribute name="type">application/atom+xml</xsl:attribute>
		</xsl:element>
		<xsl:element name="link">
			<xsl:attribute name="href">
				<xsl:value-of select="concat($baseURL, $newsPageURL)"/>
			</xsl:attribute>
			<xsl:attribute name="rel">alternate</xsl:attribute>
			<xsl:attribute name="type">text/html</xsl:attribute>
		</xsl:element>
		<updated>
			<xsl:call-template name="getISO8601FullDate">
				<xsl:with-param name="fullDate" select="news:new[last()]/news:fullDate"/>
			</xsl:call-template>
		</updated>
		<author>
			<name>LUSI project</name>
		</author>
		<id>
			<xsl:value-of select="concat($baseURL, $feedURL)"/>
		</id>
	</xsl:template>
	
	<!--
		Creates the number of latest entries specified in numberOfNews global parameter.
		
		The news, in the input XML document, are ordered chronologically: older news are first.
		The entries in the feed should be ordered in inverse chronological order, so they're sorted
		this way. However, the "new" matching templates should take this into account.
	-->
	<xsl:template name="feedEntries">
		<xsl:apply-templates select="news:new">
			<xsl:sort order="ascending"/>
		</xsl:apply-templates>
	</xsl:template>
	
	<!--
		Creates an entry element for the feed.
		It includes title, summary, link, id and updating date.
		Title is set to the title of the new.
		Summary is set to the summary of the new, which must be in XHTML.
		Link and id are set to the HTML version of the new.
		Updating date is set to the ISO8601 version of the date.
		
		Only the latest $numberOfNews are created.
		News are matched in ascending order (thus chronologically inverse),
		so the id of the new is its inverse position (indexed at 1).
	-->
	<xsl:template match="news:new">
		<xsl:if test="position()&lt;=$numberOfNews">
			<entry>
				<title>
					<xsl:value-of select="news:title"/>
				</title>
				<summary type="xhtml">
					<div xmlns="http://www.w3.org/1999/xhtml">
						<xsl:apply-templates select="news:summary/*"/>
					</div>
				</summary>
				<xsl:element name="link">
					<xsl:attribute name="href">
						<xsl:call-template name="getNewLink">
							<xsl:with-param name="number" select="last()-position()+1"/>
						</xsl:call-template>
					</xsl:attribute>
				</xsl:element>
				<id>
					<xsl:call-template name="getNewLink">
						<xsl:with-param name="number" select="last()-position()+1"/>
					</xsl:call-template>
				</id>
				<updated>
					<xsl:call-template name="getISO8601FullDate">
						<xsl:with-param name="fullDate" select="news:fullDate"/>
					</xsl:call-template>
				</updated>
			</entry>
		</xsl:if>
	</xsl:template>
	
	<!--
		Matches all the summary child elements.
		Summary child elements are XHTML elements. They're copied directly to the output,
		provided there's not a matching template. If a matching template is found,
		it's applied and its output copied to the general output.
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
		Modifies the reference in links.
		If the link was absolute (contains a '://' protocol string), it's copied literally.
		Otherwise, the link is relative, so the address is prefixed with the base URL.
	-->
	<xsl:template match="@href">
		<xsl:attribute name="href">
			<xsl:choose>
				<xsl:when test="contains(.,'://')">
					<xsl:value-of select="."/>
				</xsl:when>
				<xsl:otherwise>
					<xsl:value-of select="concat($baseURL, .)"/>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:attribute>
	</xsl:template>
	
	<!--
		Returns a link to the specified new.
		The link is (baseURL)(newsPageURL)#newId(newPosition)
		
		@param number The number of the new.
	-->
	<xsl:template name="getNewLink">
		<xsl:param name="number"/>
		
		<xsl:value-of select="concat($baseURL, $newsPageURL, '#newId', $number)"/>
	</xsl:template>

	<!--
		Returns the ISO8601 version of a full date (date and time).
		The fullDate must contain a date and, optionally, a time.
		If present, date or date and time are assumed to follow RFC 3339 (not
		including the separation 'T' between them).
		If time is missed, the defaultTime is used instead.
		
		@param fullDate The full date to convert.
	-->
	<xsl:template name="getISO8601FullDate">
		<xsl:param name="fullDate"/>

		<xsl:choose>
			<xsl:when test="$fullDate/news:time != ''">
				<xsl:value-of select="concat($fullDate/news:date, 'T', $fullDate/news:time)"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="concat($fullDate/news:date, 'T', $defaultTime)"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
</xsl:stylesheet>
