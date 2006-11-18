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
Adds special links to compound lists so sublists can be folded and unfolded.

Each sublist (a list in a list item) of the list with class "foldableList" are
made foldable. Every sublist is unfolded at the beginning.

When the "fold" link (represented by a "-") in an unfolded list is clicked, all
the sublists are removed from the item list and the "fold" link changes to
"unfold".
When the "unfold" link (represented by a "+") in a folded list is clicked, all
the sublists are added again to the item list and the "unfold" link changes to
"fold".

No style is applied to the generated elements. The only new elements added are
the fold/unfold links, which belong to "foldLink" class, so they can be styled
with CSS.

Elements are added and removed instead of only shown or hidden using CSS, so it
works even when no stylesheets are used.


HOW DOES IT WORK?
-----------------
All the root lists with "foldableList" class are selected and made foldable.
Root list referes to class with "foldableList" class which aren't child (direct
or deep) of another list with "foldableList" class.

When a list is made foldable, all its list item are checked to know if they can
be made foldable. A list item can be made foldable if it contains at least one
list (ordered or unordered). All the list items that can be made foldable are
made foldable recursively. In each foldable list item a link is inserted before
the first child. This link will fold or unfold the list, depending on the state.

When a list item is folded, the list item is copied to an array of folded lists.
It's cloned, and all the child lists are removed from the clone. The original
list item is then substituted in the document by its clone. The link to fold in
the clone is also changed to unfold to reflect the new state.

When a list item is unfolded, the previously saved original list item is put
again in the document replacing the folded clone.


LIST THAT CAN BE MADE FOLDABLE EXAMPLE
--------------------------------------
The XML below shows an example of a list that can be made foldable. It's simply
a two levels list.

<ul class="foldableList">
  <li>Item 1
    <ul>
      <li>Item 1.1</li>
      <li>Item 1.2</li>
    </ul>
  </li>
  <li>Item 2</li>
  <li>Item 3
    <ul>
      <li>Item 3.1</li>
      <li>Item 3.2
        <ul>
          <li>Item 3.2.1</li>
        </ul>
      </li>
    </ul>
  </li>
</ul>

The shown foldable list will be:
* -Item 1
    * Item 1.1
    * Item 1.2
* Item 2
* -Item 3
    * Item 3.1
    * -Item 3.2
        * Item 3.2.1


TESTED WITH:
------------
-Mozilla Firefox 1.0.2 (should work with all the Gecko based browsers)
-Konqueror 3.4 (should work with all the KHTML based browsers)


*/

/******************************************************************************
 *                                                                            *
 *                                PROTOYPES                                   *
 *                                                                            *
 *****************************************************************************/

/**
 * Adds an item to the array in the first empty position and returns the
 * position.
 * If no empty position was found the item is appended.
 *
 * @param item The item to be added.
 * @return The position where the item was added.
 */
Array.prototype.add = function(item) {
  var i;
  for (i=0; i<this.length; i++) {
    if (this[i] == null) {
      this[i] = item;
      return i;
    }
  }

  this.push(item);

  return i;
}


/******************************************************************************
 *                                                                            *
 *                           FOLDABLE LISTS FUNCTIONS                         *
 *                                                                            *
 *****************************************************************************/

/**
 * A list containing all the folded lists.
 */
var foldedLists;

/**
 * Makes all the lists (ordered or unordered) with class "foldableList"
 * foldables.
 * A foldable list has a special link in each sublist so they can be hidden or
 * shown. Every sublist of a foldable list is foldable, no matter how deep it
 * is. Child lists can also have class "foldableList", but it's superfluous.
 */
function makeListsFoldable() {
  if (!scriptCanBeHandled()) {
    return;
  }

  foldedLists = [];

  var selectedLists = getListsToMakeFoldable();

  var i;
  for (i=0; i<selectedLists.length; i++) {
    makeListFoldable(selectedLists[i]);
  }
}

/**
 * Checks if the browser implementes all the needed ECMAScript bindings for the
 * script.
 * This script uses DOM Level 2 Core and DOM Level 2 Events module.
 *
 * @return True if the browser conforms to the needed modules, false otherwise.
 */
function scriptCanBeHandled() {
  if (!(document.implementation.hasFeature("Core", "2.0") &&
        document.implementation.hasFeature("Events", "2.0"))) {
    return false;
  }

  return true;
}

/**
 * Makes the specified list foldable.
 * All the child nodes are checked and, if they can be foldable, are made
 * foldable recursively.
 *
 * @param list The list to be made foldable.
 */
function makeListFoldable(list) {
  var childNodes = list.childNodes;

  var i;
  for (i=0; i<childNodes.length; i++) {
    if (childNodes[i].nodeType == Node.ELEMENT_NODE &&
        childNodes[i].tagName.toLowerCase() == "li") {

        makeListElementFoldable(childNodes[i]);
    }
  }
}

/**
 * Checks if a list item should be made foldable and, if it should, makes it.
 * A list item should be made foldable if it contains any list (ordered or
 * unordered). When made foldable, a link is added in the list item before any
 * other child. This link will fold or unfold the list depending on the state.
 * An event listener is added to the link so it can handle click events.
 *
 * @param listItem The list item to be made foldable.
 */
function makeListElementFoldable(listItem) {
  var childNodes = listItem.childNodes;

  var makeFoldable = false;

  var i;
  for (i=0; i<childNodes.length; i++) {
    if (childNodes[i].nodeType == Node.ELEMENT_NODE &&
        (childNodes[i].tagName.toLowerCase() == "ul" ||
         childNodes[i].tagName.toLowerCase() == "ol")) {
      makeFoldable = true;

      makeListFoldable(childNodes[i]);
    }
  }

  if (makeFoldable) {
    var foldLink = document.createElement("a");
    foldLink.setAttribute("class", "foldLink");
    foldLink.setAttribute("href", "#fold");
    foldLink.setAttribute("title", "Fold this menu");
    foldLink.appendChild(document.createTextNode("-"));

    foldLink.addEventListener("click", foldMenuHandler, false);

    listItem.insertBefore(foldLink, listItem.firstChild);
  }
}

/**
 * Hanlder for click event in the fold link in an unfolded list.
 * The list item is saved, and replaced by a copy of that list item with child
 * list elements removed. The list item is saved in the first free position in
 * the foldedLists array. This position is added to the href so it can be later
 * (when unfolding) retrieved.
 * The unfold link in the cloned (and folded) list is edited so it reflects its
 * new function (unfold instead of fold).
 */
function foldMenuHandler(event) {
  var listItem = event.currentTarget.parentNode;

  var position = foldedLists.add(listItem);

  var listItemClone = listItem.cloneNode(true);
  var childNodes = listItemClone.childNodes;

  var i;
  for (i=0; i<childNodes.length; i++) {
    if (childNodes[i].nodeType == Node.ELEMENT_NODE &&
        (childNodes[i].tagName.toLowerCase() == "ul" ||
         childNodes[i].tagName.toLowerCase() == "ol")) {
      listItemClone.removeChild(childNodes[i]);
    }
  }

  listItem.parentNode.replaceChild(listItemClone, listItem);
  var foldLink = listItemClone.firstChild;

  foldLink.setAttribute("href", "#unfold" + position);
  foldLink.setAttribute("title", "Unfold this menu");

  foldLink.replaceChild(document.createTextNode("+"), foldLink.firstChild);

  foldLink.removeEventListener("click", foldMenuHandler, false);
  foldLink.addEventListener("click", unfoldMenuHandler, false);
}

/**
 * Hanlder for click event in the unfold link in a folded list.
 * The unfolded list item is get from the saved list items using the id in the
 * href element of the link. The current list item is replaced by the saved (and
 * unfolded) list item.
 */
function unfoldMenuHandler(event) {
  var foldLink = event.currentTarget;
  var listItem = foldLink.parentNode;

  //"#unfold" length is 7
  var position = foldLink.getAttribute("href").substring(7);

  listItem.parentNode.replaceChild(foldedLists[position], listItem);
  foldedLists[position] = null;
}



/******************************************************************************
 *                                                                            *
 *                             GET ELEMENTS                                   *
 *                                                                            *
 *****************************************************************************/

/**
 * Returns an array with all the list to make foldable.
 * All the root list elements of "foldableList" class are selected. Lists can be
 * unordered or ordered.
 * If two lists, A and B, have "foldableList" class, and B is child (direct or
 * deep) of A, only A is returned.
 *
 * Any element other element of "foldableList" class is ignored.
 *
 * @return All the lists to make foldable.
 */
function getListsToMakeFoldable() {
  var selectedElementsByClass = getRootElementsByClass(
                                          document.documentElement,
                                          "foldableList");
  var selectedElements = [];

  var i;
  for (i=0; i<selectedElementsByClass.length; i++) {
    if (selectedElementsByClass[i].tagName.toLowerCase() == "ul" ||
        selectedElementsByClass[i].tagName.toLowerCase() == "ol") {
      selectedElements.push(selectedElementsByClass[i]);
    }
  }

  return selectedElements;
}

/**
 * Returns all the root child elements of "element" with the specified class
 * name (or the element itself if it's from the specified class).
 * All the root children are returned, not only direct root children.
 *
 * The term root child refers to an element which is from the specified class
 * and hasn't an ancestor also from that class. That is, if two elements, A and
 * B, have the specified class, and B is child (direct or deep) of A, only A is
 * returned.
 *
 * @param element The element to get the elements from.
 * @param className The class name of the elements to get.
 * @return An array with all the root elements of the specified class.
 */
function getRootElementsByClass(element, className) {
  var selectedElements = [];

  var added = false;
  var elementClasses = element.className.split(" ");
  var i;
  for (i=0; !added && i<elementClasses.length; i++) {
    if (elementClasses[i] == className) {
      selectedElements.push(element);
      added = true;
    }
  }

  if (added) {
    return selectedElements;
  }

  var directChildElements = [];
  getDirectChildElements(element, directChildElements);

  for (i=0; i<directChildElements.length; i++) {
    selectedElements = selectedElements.concat(getRootElementsByClass(
                                                    directChildElements[i],
                                                    className));
  }

  return selectedElements;
}

/**
 * Appends all the child elements of "element" in the array "elementsList".
 * Children are added only if they're true elements, not if they're only nodes.
 *
 * Only direct children are appended.
 *
 * @param element The element to add its children.
 * @param elementsList The list to append the elements to.
 */
function getDirectChildElements(element, elementsList) {
  var childNodes = element.childNodes;

  var i;
  for (i=0; i<childNodes.length; i++) {
    if (childNodes[i].nodeType == Node.ELEMENT_NODE) {
      elementsList.push(childNodes[i]);
    }
  }
}
