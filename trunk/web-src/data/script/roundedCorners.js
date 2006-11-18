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

This script adds rounded corners to the specified elements through a selector
using ECMAscript binding for the Level 2 Document Object Model Core and
Document Object Model Level 2 Style.

Elements can be selected by tag name, by class (prefixing the class name
with ".") and by id (prefixing the id name with "#"). Also, nested elements can
be specified (for example, all the h2 elements of class "h2Rounded" in the
element identified by "wrapper" can be selected using this: "#wrapper
.h2Rounded h2").

The script lets specify which corners should be rounded with keywords:
all, top, bottom, left, right, topLeft, topRight, bottomLeft, bottomRight or
any not overlapping combination of them (that is, you can't set "top topLeft"
to be rounded, but you can set "top bottomLeft").

The background of the element is used for the corners. If the element has a
border with 1px width, the rounded corners use a solid 1px border. Please see
limitations section for more information about this.

The rounded corners are added to the element, so the element has a 5px extra
height for each rounded corners group (5px for the top corners, 5px for the
bottom corners).


HOW DOES IT WORK?
-----------------

The script adds a div element before or after the element (depending on if the
corners must be rounded in the top or in the bottom). This div contains other 4
divs with different margins (5, 3, 2 and 1px) and heights (1, 1, 2 and 1px)
giving a rounded appearance to the corners.


LIMITATIONS:
------------

If applied in an element with a border, the border must be 1px width (not even
thin, only 1px width is valid) and solid style.

If applied in an element with margins set, those must be set in px. Relative
values such as em aren't allowed. If you need relative values, wrap the element
of which corners are going to be rounded with another element and apply a
padding to the wrapper element with the same values as the wrapped elements has
as margins.
This happens because the CSS Object Model doesn't provide an access to the
specified or actual values of the CSS cascade, as can be read here:
http://www.w3.org/TR/DOM-Level-2-Style/css.html#CSS-CSSStyleDeclaration
Computed values are always absolute, so there's no way (at least, known by me)
to know if a value is set as relative or absolute in the apecified values.

If the element has defined pseudo-classes, those aren't taken into account in
the corners. So, for example, if an element changes it's color with hover, the
rounded corners won't change.

If the same element is selected through two different calls to roundCorners
(for example, a tag name such as "h2" and a header such as "#head") both calls
apply corners to the element, thus creating double corners.


TESTED WITH:
------------
-Mozilla Firefox 1.0.2 (should work with all the Gecko based browsers)
-Konqueror 3.4 (should work with all the KHTML based browsers)


TODO:
-----

-Make it work with explorer? Take a look here:
http://www.robertnyman.com/2006/04/24/get-the-rendered-style-of-an-element/
It seems that it doesn't follow ECMAScript bindings...

-Refactor createLines method.

-Support pseudo-classes through ECMAScript event handlindg.

-Anti-aliasing for corners.

*/

/******************************************************************************
 *                                                                            *
 *                                PROTOYPES                                   *
 *                                                                            *
 *****************************************************************************/

/**
 * Returns true if the searched string is contained in the string on which
 * it's invoked.
 *
 * @param searchedString The string being searched.
 * @return True if it's contained, false otherwise.
 */
String.prototype.contains = function(searchedString) {
  return (this.indexOf(searchedString) >= 0 ? true : false);
}

/**
 * Replaces the exact match of a string with other string.
 * An exact match has a white space before and after the string to match.
 *
 * @param findString The string to be replaced.
 * @param newString The string to replace with.
 * @return A string with the exact matches of findString replaced with
 *         newString.
 */
String.prototype.replaceExact = function(findString, newString) {
  if (!this.contains(findString)) {
    return this;
  }

  var returnString = "";
  var splitString = this.split(" ");

  var i;
  for (i=0; i<splitString.length; i++) {
    if (splitString[i] == findString) {
      splitString[i] = newString;
    }
    returnString = returnString + splitString[i] + " ";
  }

  //Removes last white space
  returnString = returnString.substring(0, returnString.length-1);

  return returnString;
}


/**
 * Returns a copy of the array joined with the items of the specified array
 * which doesn't already exist in the array.
 *
 * @param The array to be concatenated.
 * @return A copy of the array joined with the non-repeated items of the second
 *         array.
 */
Array.prototype.concatUnique = function(arrayToConcat) {
  var returnArray = [];
  returnArray = this.concat(returnArray);

  var i;
  for (i=0; i<arrayToConcat.length; i++) {
    if (!this.contains(arrayToConcat[i])) {
      returnArray.push(arrayToConcat[i]);
    }
  }

  return returnArray;
}

/**
 * Returns true if the array contains the specified item.
 *
 * @param item The item to be checked.
 * @return True if the array already contains the item, false otherwise.
 */
Array.prototype.contains = function(item) {
  var i;
  for (i=0; i<this.length; i++) {
    if (this[i] == item) {
      return true;
    }
  }

  return false;
}

/******************************************************************************
 *                                                                            *
 *                           ROUND FUNCTIONS                                  *
 *                                                                            *
 *****************************************************************************/

/**
 * Adds rounded corners to the specified elements.
 * Elements can be selected by tag name, by class (prefixing the class name
 * with ".") and by id (prefixing the id name with "#"). Also, nested elements
 * can be specified (for example, all the h2 elements of class "h2Rounded" in
 * the element identified by "wrapper" can be selected using this: "#wrapper
 * .h2Rounded h2").
 *
 * Options can be: all, top, bottom, left, right, topLeft, topRight,
 * bottomLeft, bottomRight or any not overlapping combination of them (that is,
 * you can't set "top topLeft" to be rounded, but you can set
 * "top bottomLeft").
 *
 * @param selector The selector that identifies the elements that will be
 *                 rounded.
 * @param options The options to apply when rounding the corners.
 */
function roundCorners(selector, options) {
  if (!scriptCanBeHandled()) {
    return;
  }

  options = options.replaceExact("all", "top bottom");
  options = options.replaceExact("top", "topLeft topRight");
  options = options.replaceExact("bottom", "bottomLeft bottomRight");
  options = options.replaceExact("left", "topLeft bottomLeft");
  options = options.replaceExact("right", "topRight bottomRight");

  var selectedElements = getElements(selector);

  if (options.contains("top")) {
    sides = getSides(options, "top");
    roundTop(selectedElements, sides);
  }
  if (options.contains("bottom")) {
    sides = getSides(options, "bottom");
    roundBottom(selectedElements, sides);
  }
}

/**
 * Checks if the browser implementes all the needed ECMAScript bindings for the
 * script.
 * This script uses DOM Level 2 Core and DOM Level 2 CSS2 module. However, CSS2
 * module isn't truly checked. Instead, the needed objects availability is
 * checked, as browsers like Konqueror which can handle all the needed objects
 * doesn't fully support the binding.
 *
 * @return True if the browser conforms to the needed modules, false otherwise.
 */
function scriptCanBeHandled() {
  if (!(document.implementation.hasFeature("Core", "2.0") && checkCSS2())) {
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
  var createdElement = document.createElement("div");

  if (!(document.defaultView && document.defaultView.getComputedStyle &&
      createdElement.style)) {
    return false;
  }

  return true;
}

/**
 * Returns which side should be rounded for a position (top or bottom) based
 * on the options.
 *
 * @param options The options from where the sides must be got.
 * @param position "top" or "bottom".
 * @return "left", "right" or "both", depending on which side should be
 *         rounded.
 */
function getSides(options, position) {
  sides = "";
  if (options.contains(position + "Left")) {
    sides = "left";
  }
  if (options.contains(position + "Right")) {
    sides = sides.concat("right");
  }
  sides = sides.replace("leftright", "both");

  return sides;
}

/**
 * Rounds the specified top corners of the elements.
 *
 * @param selectedElements The elements to round their top corners.
 * @param sides "left", "right" or "both", depending on the sides that must be
 *              rounded.
 */
function roundTop(selectedElements, sides) {
  var i;
  for (i=0; i<selectedElements.length; i++) {
    roundTopElement(selectedElements[i], sides);
  }
}

/**
 * Rounds the specified bottom corners of the elements.
 *
 * @param selectedElements The elements to round their bottom corners.
 * @param sides "left", "right" or "both", depending on the sides that must be
 *              rounded.
 */
function roundBottom(selectedElements, sides) {
  var i;
  for (i=0; i<selectedElements.length; i++) {
    roundBottomElement(selectedElements[i], sides);
  }
}

/**
 * Rounds the specified top corners of the element.
 *
 * @param element The element to round its top corners.
 * @param sides "left", "right" or "both", depending on the sides that must be
 *              rounded.
 */
function roundTopElement(element, sides) {
  var linesWrapper = createLinesWrapper(element, "Top");
  var lines = createLines(element, "Top", sides);

  var i;
  for (i=0; i<lines.length; i++) {
    linesWrapper.appendChild(lines[i]);
  }

  element.parentNode.insertBefore(linesWrapper, element);
}

/**
 * Rounds the specified bottom corners of the element.
 *
 * @param element The element to round its bottom corners.
 * @param sides "left", "right" or "both", depending on the sides that must be
 *              rounded.
 */
function roundBottomElement(element, sides) {
  var linesWrapper = createLinesWrapper(element, "Bottom");
  var lines = createLines(element, "Bottom", sides);

  var i;
  for (i=lines.length-1; i>=0; i--) {
    linesWrapper.appendChild(lines[i]);
  }

  //Firefox adds in some cases a strange bottom margin if the element is added
  //before the text node. I have no idea of why it happens.
  if (element.nextSibling != null &&
      element.nextSibling.nodeType == Node.TEXT_NODE) {
    element.parentNode.insertBefore(linesWrapper,
                                    element.nextSibling.nextSibling);
  } else {
    element.parentNode.insertBefore(linesWrapper, element.nextSibling);
  }
}

/**
 * Creates the wrapper div for the 4 inner divs.
 * The left and right margins of the wrapper are equal to the ones of the
 * element. Top margin is only taken into account when the position of the div
 * is at the top of the element. The same happens with bottom margin. Moreover,
 * in case of top and bottom margins, they're removed from the element.
 *
 * This only works if the margins are set in absolute units. If they're set in
 * relative units, when zooming in or out the text, the margins won't be
 * resized (because the absolute values are used).
 *
 * @param element The element to which the rounded corners are going to be
 *                added.
 * @param position "Top" or "Bottom", depending on the position of the corners.
 *                 This parameter is case sensitive.
 */
function createLinesWrapper(element, position) {
  var marginLeft = document.defaultView.getComputedStyle(element, null)["marginLeft"];
  var marginRight = document.defaultView.getComputedStyle(element, null)["marginRight"];

  var createdElement = document.createElement("div");

  createdElement.style.marginLeft = marginLeft;
  createdElement.style.marginRight = marginRight;

  if (position == "Top") {
    var marginTop = document.defaultView.getComputedStyle(element, null)["marginTop"];
    createdElement.style.marginTop = marginTop;
    element.style.marginTop = "0";
  } else if (position == "Bottom") {
    var marginBottom = document.defaultView.getComputedStyle(element, null)["marginBottom"];
    createdElement.style.marginBottom = marginBottom;
    element.style.marginBottom = "0";
  }

  return createdElement;
}

/**
 * Creates the 4 inner divs which make the rounded corners.
 * The background is get from the element itself.
 *
 * If the element has a border with 1px width, the rounded corners use a solid
 * 1px border. No other borders are supported.
 *
 * @param element The element to which the rounded corners are going to be
 *                added.
 * @param position "Top" or "Bottom", depending on the position of the corners.
 *                 This parameter is case sensitive.
 * @param sides "left", "right" or "both", depending on the side of the
 *              corners. This parameter is case sensitive.
 */
function createLines(element, position, sides) {
  var lines = [];

  var backgroundColor = document.defaultView.getComputedStyle(element, null)["backgroundColor"];
  var borderColor = document.defaultView.getComputedStyle(element, null)["border" + position + "Color"];
  var borderWidth = document.defaultView.getComputedStyle(element, null)["border" + position + "Width"];

  //KHTML doesn't recognizes this value, so it won't be used
  var borderStyle = document.defaultView.getComputedStyle(element, null)["border" + position + "Style"];

  var numberOfLines = 4;
  var i;
  for (i=0; i<numberOfLines; i++) {
    var createdElement = document.createElement("div");

    if (i==3) {
      createdElement.style.height = "2px";
    } else {
      createdElement.style.height = "1px";
    }

    createdElement.style.marginTop = "0";
    createdElement.style.marginBottom = "0";

    if (i==0) {
      if (sides == "both" || sides == "left") {
        createdElement.style.marginLeft = "5px";
      }
      if (sides == "both" || sides == "right") {
        createdElement.style.marginRight = "5px";
      }
    } else {
      if (sides == "both" || sides == "left") {
        createdElement.style.marginLeft = (numberOfLines-i) + "px";
      }
      if (sides == "both" || sides == "right") {
        createdElement.style.marginRight = (numberOfLines-i) + "px";
      }
    }

    createdElement.style.backgroundColor = backgroundColor;

    if (borderWidth != null && borderWidth == "1px") {
        createdElement.style.borderStyle = "none solid";
        createdElement.style.borderWidth = borderWidth;
        createdElement.style.borderColor = borderColor;

      if (i==0) {
        createdElement.style.backgroundColor = borderColor;
      } else if (i==1) {
        if (sides == "both" || sides == "left") {
          createdElement.style.borderLeftWidth = "2px";
        }
        if (sides == "both" || sides == "right") {
          createdElement.style.borderRightWidth = "2px";
        }
      }
    }

    lines.push(createdElement);
  }

  if (position == "Bottom") {
    element.style.borderBottomStyle = "none";
  } else if (position == "Top") {
    element.style.borderTopStyle = "none";
  }

  return lines;
}

/******************************************************************************
 *                                                                            *
 *                             GET ELEMENTS                                   *
 *                                                                            *
 *****************************************************************************/

/**
 * Returns an array with all the selected elements, based on the selector.
 * Elements can be searched by tag name, by class (prefixing the class name
 * with ".") and by id (prefixing the id name with "#"). Also, nested elements
 * can be specified (for example, all the h2 elements of class "h2Rounded" in
 * the element identified by "wrapper" can be selected using this: "#wrapper
 * .h2Rounded h2").
 *
 * @param selector The selector to use.
 * @return All the elements matched.
 */
function getElements(selector) {
  var selectedElements = [document.documentElement];

  var selectors = selector.split(" ");
  var i;
  for (i=0; i<selectors.length; i++) {
    var selectedChildElements = [];

    var j;
    for (j=0; j<selectedElements.length; j++) {
      selectedChildElements = selectedChildElements.concatUnique(
                          getChildElements(selectedElements[j], selectors[i]));
    }

    selectedElements = selectedChildElements;
  }

  return selectedElements;
}

/**
 * Returns all the elements child of "element", based on the selector.
 * Elements can be searched by tag name, by class (prefixing the class name
 * with ".") and by id (prefixing the id name with "#"). Selector can be only
 * one of those, but not nested selectors like "#header p".
 *
 * All the children are returned, not only direct children.
 *
 * @param element The element to get the elements from.
 * @param selector The selector to use.
 * @return All the elements matched.
 */
function getChildElements(element, selector) {
  var selectedElements = [];

  if (selector.indexOf(".") == 0) {
    selector = selector.substring(1);
    selectedElements = getElementsByClass(element, selector);
  } else if (selector.indexOf("#") == 0) {
    selector = selector.substring(1);
    var selectedElement = getElementsById(element, selector);
    if (selectedElement != null) {
      selectedElements.push(selectedElement);
    }
  } else {
    selectedElements = element.getElementsByTagName(selector);
  }

  return selectedElements;
}

/**
 * Returns all the child elements of "element" with the specified class name.
 * All the children are returned, not only direct children.
 *
 * @param element The element to get the elements from.
 * @param className The class name of the elements to get.
 * @return An array with all the elements of the specified class.
 */
function getElementsByClass(element, className) {
  var selectedElements = [];

  var allElements = [];
  getAllElements(element, allElements);

  var i;
  for (i=0; i<allElements.length; i++) {
    var elementClasses = allElements[i].className.split(" ");
    var added = false;
    var j;
    for (j=0; !added && j<elementClasses.length; j++) {
      if (elementClasses[j] == className) {
        selectedElements.push(allElements[i]);
        added = true;
      }
    }
  }

  return selectedElements;
}

/**
 * Return the child element of "element" with the specified id.
 * All the children are returned, not only direct children.
 *
 * ECMAScript binding only defines getElementById for Documents, but not for
 * elements, so that's why this method was made.
 *
 * @param element The element to get the element from.
 * @param id The id of the element to get.
 * @return The element with the specified id.
 */
function getElementsById(element, id) {
  var selectedElement;

  var allElements = [];
  getAllElements(element, allElements);

  var found = false;
  var i;
  for (i=0; !found && i<allElements.length; i++) {
    var elementId = allElements[i].id;
    if (elementId == id) {
      selectedElement = allElements[i];
      found = true;
    }
  }

  return selectedElement;
}

/**
 * Appends all the child elements, and the element itself, of "element" in the
 * array "elementsList".
 * Children and the element itself are added only if they're true elements, not
 * if they're only nodes.
 *
 * All the children are returned, not only direct children.
 *
 * @param element The element to add its children and itself.
 * @param elementsList The list to append the elements to.
 */
function getAllElements(element, elementsList) {
  if (element.nodeType == Node.ELEMENT_NODE) {
    elementsList.push(element);
  }

  var childNodes = element.childNodes;
  var i;
  for (i=0; i<childNodes.length; i++) {
    getAllElements(childNodes[i], elementsList);
  }
}
