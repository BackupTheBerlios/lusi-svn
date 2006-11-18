/***************************************************************************
 *   Copyright (C) 2006 by Daniel Calviño Sánchez                          *
 *   kalvy@users.berlios.de                                                *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this library; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/******************************************************************************
 *                                                                            *
 *                         DESCRIPTION OF THIS SCRIPT                         *
 *                                                                            *
 *****************************************************************************/

/*

DESCRIPTION
-----------
Generates a screenshot gallery from a list of screenshots with a specific
structure.

When an item of the list is clicked, it shows an individual screenshot with the
screenshot title, a screenshots counter and a navigation bar to go to the
previous and next screenshots, if any. The individual screenshots, when clicked
on them, show the full size screenshots. Individual screenshots also resize
themselves to fit in the window each time it is resized.

No style is applied to the generated elements. However, they have specific ids,
so they can be styled with CSS. See the section "Generated screenshot structure"
for further information on the generated elements and theirs ids.


HOW DOES IT WORK?
-----------------
The screenshots list is read and stored in a variable. It's modified so each
thumbnail now is linked to the generated enlarged screenshot instead of the
full size screenshot.
Both enlarged screenshots and the screenshots list are child of the same
element: when the list is shown, the individual screenshot is removed; when an
individual screenshot is shown, the list (or another screenshot) is removed.

The needed information for each individual screenshot is got from the
screenshots list. Screenshots are identified by the number they have in the
screenshots list. Each screenshot can be shown individually appending "#number"
to the url of the page. If there's no "#number", the whole list is shown.

Resize event of the window is handled so, if there's any individual screenshot
being shown, it'll be resized every time the window is resized, so it can fit
in the available space.

Default handlers for click events aren't prevented to be executed, so the
location of the page is updated to the specified new link.


SCREENSHOTS LIST STRUCTURE
--------------------------
The XML below shows the structure the screenshots list must conform with to be
used with this script. Only one list item is shown, the others should follow the
same structure.

<ul id="screenshotsList">
  <li>
    <p>Screenshot title</p>
    <a href="path/screenshotName.extension" title="Click for full size">
      <img src="path/screenshotName-widthOfThumbnail.extension"
           alt="(Screenshot title) screenshot thumbnail"/>
    </a>
  </li>
    ...
</ul>


GENERATED SCREENSHOT STRUCTURE
------------------------------
The code below is an example of the XML elements created for every screenshot
shown. The things that change depending on each screenshot are the title of
the screenshot, the counter of screenshots, the pathname to the screenshot and
the links to the next and previous screenshots.

<div id="screenshot">
  <p id="screenshotTitle">The title of the screenshot</p>
  <p>2/3</p>
  <p id="screenshotImageWrapper">
    <a id="screenshotImageLink" href="images/aScreenshot.jpg"
       title="Click for full size">
      <img width="(a number that depends on window size)" id="screenshotImage"
           src="images/aScreenshot.jpg"
           alt="Current screenshot: images/aScreenshot.jpg"/>
    </a>
  </p>
  <div id="navigationBar">
    <p id="nextWrapper">
      <a href="path/page.html#0" title="Next screenshot">&lt; Previous</a>
    </p>
    <p id="upWrapper">
      <a href="path/page.html" title="Screenshots list">Up</a>
    </p>
    <p id="nextWrapper">
      <a href="path/page.html#2" title="Next screenshot">Next &gt;</a>
    </p>
  </div>
</div>


LIMITATIONS:
------------
If a screenshot or the screenshot list are currently loaded, changing the url
in the address bar from page.html#number to page.html#otherNumber (for example)
won't do anything. Once the url is changed, the page must be refreshed.


TESTED WITH:
------------
-Mozilla Firefox 1.0.2 (should work with all the Gecko based browsers)
-Konqueror 3.4 (should work with all the KHTML based browsers)


*/


/******************************************************************************
 *                                                                            *
 *                        GALLERY GENERATOR fUNCTIONS                         *
 *                                                                            *
 *****************************************************************************/

/**
 * The URL of the page with the list of screenshots.
 */
var screenshotsURL;

/**
 * The element to append screenshots and the screenshots list to.
 */
var screenshotsParent;

/**
 * The next sibling to the screenshots and the screenshots list.
 */
var screenshotsNextSibling;

/**
 * The list containing all the screenshots.
 */
var screenshotsList;

/**
 * The current screenshots being shown, if any.
 */
var currentScreenshot;

/**
 * The number of the current screenshots being shown, if any.
 */
var currentScreenshotNumber;

/**
 * The item in the screenshots list of the current screenshot being shown, if
 * any.
 */
var currentScreenshotListItem;

/**
 * Generates the screenshots gallery, and shows it or a concrete screenshot
 * depending on the URL.
 * It modifies the default list to make links point to the enlarged screenshot
 * instead of the full size screenshot.
 * If the URL has the form "path/page.html#number", it shows the screenshot with
 * that number (or first or last screenshot, if the number is out of range).
 * Otherwise, it shows the screenshots list.
 */
function generateGallery() {
  if (!scriptCanBeHandled()) {
    return;
  }

  screenshotsList = document.getElementById("screenshotsList");

  if (document.URL.indexOf('#') < 0) {
    screenshotsURL = document.URL;
  } else {
    screenshotsURL = document.URL.substring(0, document.URL.indexOf('#'));
  }

  //Prepares the screenshots list
  var linksList = screenshotsList.getElementsByTagName("a");
  var i;
  for (i=0; i<linksList.length; i++) {
    linksList[i].setAttribute("href", screenshotsURL + "#" + i);
    linksList[i].setAttribute("title", "Click to enlarge");
    linksList[i].addEventListener("click", showScreenshotHandler, false);
  }

  //No screenshot is currently being shown
  currentScreenshot = null;
  currentScreenshotNumber = -1;
  currentScreenshotListItem = null;

  if (screenshotsList.getElementsByTagName("li")[0]) {
    screenshotsNextSibling = screenshotsList.nextSibling;
    screenshotsParent = screenshotsList.parentNode;

    var screenshotNumber = getScreenshotNumberFromURL(document.URL);

    if (screenshotNumber != -1) {
      setNewScreenshot(screenshotNumber);
    } else {
      showScreenshotsList();
    }

    onresize = updateScreenshotSize;
  }
}

/**
 * Checks if the browser implementes all the needed ECMAScript bindings for the
 * script.
 * This script uses DOM Level 2 Core, DOM Level 2 HTML module and DOM Level 2
 * Events module and DOM Level 2 CSS2 module.
 *
 * However, CSS2 module isn't truly checked. Instead, the needed objects
 * availability is checked, as browsers like Konqueror which can handle all the
 * needed objects doesn't fully support the binding.
 *
 * @return True if the browser conforms to the needed modules, false otherwise.
 */
function scriptCanBeHandled() {
  if (!(document.implementation.hasFeature("Core", "2.0") &&
        document.implementation.hasFeature("Events", "2.0") &&
        document.implementation.hasFeature("HTML", "2.0") &&
        checkCSS2())) {
    return false;
  }

  return true;
}

/**
 * Checks if the browser can handle all the needed DOM Level 2 CSS2 module
 * objects.
 * hasFeature() isn't used because some browsers as Konqueror can handle all the
 * needed objects but doesn't fully support the module.
 *
 * @return True if the browser can handle all the needed objects, false
 *         otherwise.
 */
function checkCSS2() {
  if (!(document.defaultView && document.defaultView.getComputedStyle)) {
    return false;
  }

  return true;
}

/**
 * Shows the screenshosts list.
 * If an enlarged screenshot is being shown, it's removed and the list shown
 * instead.
 */
function showScreenshotsList() {
  if (currentScreenshot !=null) {
    screenshotsParent.removeChild(currentScreenshot);

    currentScreenshot = null;
    currentScreenshotNumber = -1;
    currentScreenshotListItem = null;
  }

  screenshotsParent.appendChild(screenshotsList);
}

/**
 * Shows the screenshot clicked.
 * Gets the number of screenshot from the link clicked and sets that screenshot.
 */
function showScreenshotHandler(event) {
  var screenshotNumber = getScreenshotNumberFromURL(event.currentTarget.href);

  if (screenshotNumber != -1) {
    setNewScreenshot(screenshotNumber);
  }
}

/**
 * Returns the screenshot number from a URL in the form "path/page.html#number".
 * If there's no number specified in the url, or it's not a valid number, it
 * returns -1.
 *
 * @param url The url to get the screenshot number from.
 * @return The screenshot number from the URL.
 */
function getScreenshotNumberFromURL(url) {
  var screenshotNumber = -1;

  if (url.indexOf('#') >= 0) {
    screenshotNumber = parseInt(
              url.substr(url.indexOf('#') + 1));

    if (isNaN(screenshotNumber)) {
      screenshotNumber = -1;
    }
  }

  return screenshotNumber;
}

/**
 * Shows a new screenshot.
 * The screenshot is specified by its number, indexed in 0.
 * The already loaded screenshot or screenshot list is removed to show the new
 * screenshot.
 *
 * @param screenshotNumber The number of the screenshot to show.
 */
function setNewScreenshot(screenshotNumber) {
  if (currentScreenshot) {
    screenshotsParent.removeChild(currentScreenshot);
  } else {
    screenshotsParent.removeChild(screenshotsList);
  }

  screenshotsParent.insertBefore(
                createScreenshot(screenshotNumber),
                screenshotsNextSibling);
  updateScreenshotSize();
}

/**
 * Returns a div element containing the screenshot title, the screenshots
 * counter, the screenshot image and the navigation bar.
 * Screenshot number is indexed in 0. If the specified screenshot number is
 * smaller or larger than 0 or the number of screenshots available, it's set to
 * 0 or the number of the last screenshot.
 *
 * currentScreenshot, currentScreenshotNumber and currentScreenshotListItem
 * are set to the needed values.
 */
function createScreenshot(screenshotNumber) {
  var listItemElements = screenshotsList.getElementsByTagName("li");

  if (screenshotNumber < 0) {
    screenshotNumber = 0;
  } else if (screenshotNumber >= listItemElements.length) {
    screenshotNumber = listItemElements.length - 1;
  }

  var listItemElement = listItemElements[screenshotNumber];

  var divElement = document.createElement("div");
  divElement.setAttribute("id", "screenshot");

  currentScreenshot = divElement;
  currentScreenshotNumber = screenshotNumber;
  currentScreenshotListItem = listItemElement;

  //Screenshot title
  var pElement = listItemElement.getElementsByTagName("p")[0].cloneNode(true);
  pElement.setAttribute("id", "screenshotTitle");
  divElement.appendChild(pElement);

  divElement.appendChild(createScreenshotCounter());

  var thumbnailImageElement = listItemElement.getElementsByTagName("img")[0];
  divElement.appendChild(createImageLink(thumbnailImageElement));

  divElement.appendChild(createNavigationBar(listItemElement));

  return divElement;
}

/**
 * Returns a paragraph with the current number of the screenshot (indexed in 1)
 * and the total number of screenshots.
 *
 * @return The paragraph with the numbers.
 */
function createScreenshotCounter() {
  var screenshotCountText = (currentScreenshotNumber + 1) + "/" +
                    screenshotsList.getElementsByTagName("li").length;

  var screenshotCountElement = document.createElement("p");
  screenshotCountElement.appendChild(
                    document.createTextNode(screenshotCountText));

  return screenshotCountElement;
}

/**
 * Returns a link to the full image containing also this image.
 * The link uses the id "currentScreenshotImageLink" and the image uses the id
 * "currentScreenshotImage".
 * The link is wrapped in a paragraph.
 *
 * @param thumbnailImageElement The image in the screenshot thumbnail.
 * @return The link element containing the image, wrapped in a paragraph.
 */
function createImageLink(thumbnailImageElement) {
  var imageLinkWrapperElement = document.createElement("p");
  imageLinkWrapperElement.setAttribute("id", "screenshotImageWrapper");

  var imageLinkElement = document.createElement("a");
  imageLinkElement.setAttribute("id", "screenshotImageLink");

  var thumbnailImageSrc = thumbnailImageElement.getAttribute("src");
  var imageName = thumbnailImageSrc.substring(0,
                          thumbnailImageSrc.lastIndexOf("-"));
  var imageExtension = thumbnailImageSrc.substr(
                          thumbnailImageSrc.lastIndexOf("."));
  var imageSrc = imageName + imageExtension;
  imageLinkElement.setAttribute("href", imageSrc);
  imageLinkElement.setAttribute("title", "Click for full size");

  var imageElement = document.createElement("img");
  imageElement.setAttribute("id", "screenshotImage");
  imageElement.setAttribute("src", imageSrc);
  imageElement.setAttribute("alt", "Current screenshot: " + imageSrc);
  imageLinkElement.appendChild(imageElement);

  imageLinkWrapperElement.appendChild(imageLinkElement);

  return imageLinkWrapperElement;
}

/**
 * Returns the navigation bar.
 * The navigation bar includes links to the previous and next elements, and to
 * the list of screenshots.
 * If the screenshot is the first, previous link isn't added. If the screenshot
 * is the last, next link isn't added.
 *
 * @param listItemElement The list item element in the screenshots list for the
 *        current screenshot.
 * @return The navigation bar.
 */
function createNavigationBar(listItemElement) {
  var divElement = document.createElement("div");
  divElement.setAttribute("id", "navigationBar");

  var previousElement = createNavigationBarPrevious(listItemElement);
  if (previousElement) {
    divElement.appendChild(previousElement);
  }

  divElement.appendChild(createNavigationBarUp());

  var nextElement = createNavigationBarNext(listItemElement);
  if (nextElement) {
    divElement.appendChild(nextElement);
  }

  return divElement;
}

/**
 * Returns the "Previous" link for the navigation bar.
 * If the list item is the first in the list, a null element is returned.
 * The link handles clicks showing the previous screenshot in the list.
 * The link is wrapped in a paragraph.
 *
 * @param listItemElement The list item element in the screenshots list for the
 *        current screenshot.
 * @return The "Previous" link for the navigation bar, wrapped in a paragraph.
 */
function createNavigationBarPrevious(listItemElement) {
  var previousLinkWrapperElement;

  var hasPrevious = (getPreviousSiblingElement(listItemElement) != null);

  if (hasPrevious) {
    previousLinkWrapperElement = document.createElement("p");
    previousLinkWrapperElement.setAttribute("id", "previousWrapper");

    var previousLinkElement = document.createElement("a");
    previousLinkElement.appendChild(document.createTextNode("< Previous"));
    previousLinkElement.setAttribute("href", screenshotsURL + "#" +
                                                (currentScreenshotNumber - 1));
    previousLinkElement.setAttribute("title", "Previous screenshot");
    previousLinkElement.addEventListener("click", previousScreenshotHandler,
                                  false);

    previousLinkWrapperElement.appendChild(previousLinkElement);
  }

  return previousLinkWrapperElement;
}

/**
 * Returns the "Up" link for the navigation bar.
 * The link handles clicks showing the list of screenshots.
 * The link is wrapped in a paragraph.
 *
 * @return The "Up" link for the navigation bar, wrapped in a paragraph.
 */
function createNavigationBarUp() {
  var upLinkWrapperElement = document.createElement("p");
  upLinkWrapperElement.setAttribute("id", "upWrapper");

  var upLinkElementHref = screenshotsURL;
  var upLinkElement = document.createElement("a");
  upLinkElement.appendChild(document.createTextNode("Up"));
  upLinkElement.setAttribute("href", upLinkElementHref);
  upLinkElement.setAttribute("title", "Screenshots list");
  upLinkElement.addEventListener("click", upScreenshotHandler, false);

  upLinkWrapperElement.appendChild(upLinkElement);

  return upLinkWrapperElement;
}

/**
 * Returns the "Next" link for the navigation bar.
 * If the list item is the last in the list, a null element is returned.
 * The link handles clicks showing the next screenshot in the list.
 * The link is wrapped in a paragraph.
 *
 * @param listItemElement The list item element in the screenshots list for the
 *        current screenshot.
 * @return The "Next" link for the navigation bar, wrapped in a paragraph.
 */
function createNavigationBarNext(listItemElement) {
  var nextLinkWrapperElement;

  var hasNext = (getNextSiblingElement(listItemElement) != null);

  if (hasNext) {
    nextLinkWrapperElement = document.createElement("p");
    nextLinkWrapperElement.setAttribute("id", "nextWrapper");

    var nextLinkElement = document.createElement("a");
    nextLinkElement.appendChild(document.createTextNode("Next >"));
    nextLinkElement.setAttribute("href", screenshotsURL + "#" +
                                                (currentScreenshotNumber + 1));
    nextLinkElement.setAttribute("title", "Next screenshot");
    nextLinkElement.addEventListener("click", nextScreenshotHandler, false);

    nextLinkWrapperElement.appendChild(nextLinkElement);
  }

  return nextLinkWrapperElement;
}

/**
 * Handles clicks on "Previous" link.
 * Sets the screenshot to the previous screenshot of the current one.
 */
function previousScreenshotHandler(event) {
  setNewScreenshot(currentScreenshotNumber - 1);
}

/**
 * Handles clicks on "Up" link.
 * Shows the list of screenshots.
 */
function upScreenshotHandler(event) {
  showScreenshotsList();
}

/**
 * Handles clicks on "Next" link.
 * Sets the screenshot to the next screenshot of the current one.
 */
function nextScreenshotHandler(event) {
  setNewScreenshot(currentScreenshotNumber + 1);
}

/**
 * Gets the previous sibling with "element" type of the specified element.
 * This function is needed because browsers tend to add dummy text nodes between
 * element nodes.
 *
 * @param element The element to get its previous sibling.
 * @return The previous sibling of element type, or null if there is none.
 */
function getPreviousSiblingElement(element) {
  var previousElement = null;
  var previousSibling = element.previousSibling;
  while (!previousElement && previousSibling) {
    if (previousSibling.nodeType == Node.ELEMENT_NODE) {
      previousElement = previousSibling;
    }
    previousSibling = previousSibling.previousSibling;
  }

  return previousElement;
}

/**
 * Gets the next sibling with "element" type of the specified element.
 * This function is needed because browsers tend to add dummy text nodes between
 * element nodes.
 *
 * @param element The element to get its next sibling.
 * @return The next sibling of element type, or null if there is none.
 */
function getNextSiblingElement(element) {
  var nextElement = null;
  var nextSibling = element.nextSibling;
  while (!nextElement && nextSibling) {
    if (nextSibling.nodeType == Node.ELEMENT_NODE) {
      nextElement = nextSibling;
    }
    nextSibling = nextSibling.nextSibling;
  }

  return nextElement;
}

/**
 * Updates the size of the screenshot shown to fit it in the window.
 * The screenshot is set to a width equal to its parent width minus the double
 * of its left and right padding.
 * Once set the width, the browser resizes the height automatically.
 *
 * If no screenshot is being currently shown, it does nothing.
 */
function updateScreenshotSize() {
  if (!currentScreenshot) {
    return;
  }

  var parentWidth = getPixelsNumber(
          document.defaultView.getComputedStyle(
                currentScreenshot.parentNode, null)["width"]);
  var parentLeftPadding = getPixelsNumber(
          document.defaultView.getComputedStyle(
                currentScreenshot.parentNode, null)["paddingLeft"]);
  var parentRightPadding = getPixelsNumber(
          document.defaultView.getComputedStyle(
                currentScreenshot.parentNode, null)["paddingRight"]);

  var currentScreenshotImage = document.getElementById("screenshotImage");
  var imageWidth = parentWidth - parentLeftPadding * 2 - parentRightPadding * 2;
  currentScreenshotImage.setAttribute("width", imageWidth);
}

/**
 * Returns the number of pixels from a string in the form "3px", for example.
 *
 * @param pixelsString The string to get the number of pixels.
 * @return The number of pixels.
 */
function getPixelsNumber(pixelsString) {
  return pixelsString.replace("px", "");
}