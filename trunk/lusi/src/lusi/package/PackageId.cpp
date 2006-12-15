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

#include <sstream>

#include "PackageId.h"

using std::istringstream;
using std::string;

using namespace lusi::package;

/**
 * Returns the number of the subversion.
 * The number is the first block of digits until the first non digit.
 *
 * @param subversion The subversion to get its number.
 * @return The number of the subversion.
 */
int getSubversionNumber(const string& subversion) {
    uint i = 0;
    while (i < subversion.size() && isdigit(subversion[i])) {
        ++i;
    }

    istringstream toInt(subversion.substr(0, i));
    int subversionNumber;
    toInt >> subversionNumber;

    return subversionNumber;
}

/**
 * Returns the subversion qualifier of the subversion.
 * The qualifier is the first block of non digits until the next digit. The
 * hyphen isn't included (if any).
 *
 * @param subversion The subversion to get its qualifier.
 * @return The subversion qualifier of the subversion.
 */
string getSubversionQualifier(const string& subversion) {
    uint i = 0;
    while (i < subversion.size() && isdigit(subversion[i])) {
        ++i;
    }

    if (subversion[i] == '-') {
        ++i;
    }

    string qualifier;
    while (i < subversion.size() && isalpha(subversion[i])) {
        qualifier += subversion[i];
        ++i;
    }

    return qualifier;
}

/**
 * Returns the qualifier number of the subversion.
 * The qualifier is the block of digits after the qualifier.
 *
 * @param subversion The subversion to get its qualifier number.
 * @return The qualifier number of the subversion.
 */
int getSubversionQualifierNumber(const string& subversion) {
    uint i = 0;
    while (i < subversion.size() && isdigit(subversion[i])) {
        ++i;
    }

    while (i < subversion.size() && !isdigit(subversion[i])) {
        ++i;
    }

    uint begin = i;

    while (i < subversion.size() && isdigit(subversion[i])) {
        ++i;
    }

    istringstream toInt(subversion.substr(begin, i - begin));
    int subversionQualifierNumber;
    toInt >> subversionQualifierNumber;

    return subversionQualifierNumber;
}

const int SMALLER = -1;
const int EQUAL = 0;
const int GREATER = 1;

/**
 * Compares two subversions.
 * A subversion is the substring between two dots (or a dot and the limits of
 * the string)in a version string. For example, in "1.0.1-beta2", "1", "0" and
 * "1-beta2" are the subversions.
 *
 * @param subversion1 The first subversion to compare.
 * @param subversion2 The second subversion to compare.
 * @return SMALLER if the first version is smaller than the second, EQUAL if
 *         they are equal, or GREATER if the first version is greater than the
 *         second.
 */
int compareSubversions(const string& subversion1, const string& subversion2) {
    //Any of the subversions doesn't begin with a digit, so it doesn't follow
    //the regular expression
    if (!isdigit(subversion1[0]) || !isdigit(subversion2[0])) {
        return GREATER;
    }

    //Compares the number
    int subversionNumber1 = getSubversionNumber(subversion1);
    int subversionNumber2 = getSubversionNumber(subversion2);

    if (subversionNumber1 > subversionNumber2) {
        return GREATER;
    } else if (subversionNumber1 < subversionNumber2) {
        return SMALLER;
    }

    //Compares the qualifiers
    string subversionQualifier1 = getSubversionQualifier(subversion1);
    string subversionQualifier2 = getSubversionQualifier(subversion2);

    if (subversionQualifier1 == "" && subversionQualifier2 == "") {
        return EQUAL;
    } else if (subversionQualifier1 == "" && subversionQualifier2 != "") {
        return GREATER;
    } else if (subversionQualifier1 != "" && subversionQualifier2 == "") {
        return SMALLER;
    }

    if (subversionQualifier1 == "alpha" && (subversionQualifier2 == "beta" ||
                                            subversionQualifier2 == "rc")) {
        return SMALLER;
    } else if (subversionQualifier1 == "beta" && subversionQualifier2 == "rc") {
        return SMALLER;
    } else if (subversionQualifier1 != subversionQualifier2) {
        return GREATER;
    }

    //Compares the qualifier number
    int subversionQualifierNumber1 = getSubversionQualifierNumber(subversion1);
    int subversionQualifierNumber2 = getSubversionQualifierNumber(subversion2);

    if (subversionQualifierNumber1 > subversionQualifierNumber2) {
        return GREATER;
    } else if (subversionQualifierNumber1 < subversionQualifierNumber2) {
        return SMALLER;
    }

    return EQUAL;
}

//public:

bool lusi::package::versionsWeakOrdering(const string& version1,
                                         const string& version2) {
    return PackageId::compareVersions(version1, version2) < 0;
}

//TODO It doesn't fully follow the regular expression: subversion qualifiers
//are accepted in every subversion, not only in the last.
int PackageId::compareVersions(const string& version1, const string& version2) {
    uint i1 = 0;
    uint begin1 = 0;
    uint i2 = 0;
    uint begin2 = 0;
    string subversion1;
    string subversion2;

    while (i1 < version1.size() && i2 < version2.size()) {
        while (i1 < version1.size() && version1[i1] != '.') {
            ++i1;
        }

        subversion1 = version1.substr(begin1, i1 - begin1);
        ++i1;
        begin1 = i1;

        while (i2 < version2.size() && version2[i2] != '.') {
            ++i2;
        }

        subversion2 = version2.substr(begin2, i2 - begin2);
        ++i2;
        begin2 = i2;

        int comparation = compareSubversions(subversion1, subversion2);
        if (comparation != EQUAL) {
            return comparation;
        }
    }

    if (i1 >= version1.size() && i2 < version2.size()) {
        return SMALLER;
    } else if (i1 < version1.size() && i2 >= version2.size()) {
        return GREATER;
    }

    return EQUAL;
}

PackageId::PackageId(const string& name, const string& version /*= string()*/) {
    mName = name;
    mVersion = version;
}

PackageId::PackageId(const PackageId& packageId) {
    mName = packageId.mName;
    mVersion = packageId.mVersion;
}

PackageId::~PackageId() {
}

/*
inline const string& PackageId::getName() const {
    return mName;
}

inline const string& PackageId::getVersion() const {
    return mVersion;
}
*/

PackageId& PackageId::operator=(const PackageId& packageId) {
    if (&packageId == this) {
        return *this;
    }

    mName = packageId.mName;
    mVersion = packageId.mVersion;

    return *this;
}

bool PackageId::operator==(const PackageId& packageId) const {
    return mName == packageId.mName && mVersion == packageId.mVersion;
}
