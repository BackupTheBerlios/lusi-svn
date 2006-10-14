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

#ifndef LUSI_UTIL_I18N_H
#define LUSI_UTIL_I18N_H

#ifdef HAVE_CONFIG_H
#   include <config.h>
#endif

#if ENABLE_NLS

#   include <libintl.h>

/**
 * Translates the Msgid to the current LUSI language.
 * The Msgid is a const char*.
 * It uses dgettext instead of gettext, as the domain used must be the one of
 * the library, because a call simply to gettext may use the domain from the
 * application using the library.
 */
#   define _(Msgid) dgettext(PACKAGE, Msgid)

/**
 * _(Msgid) equivalent using extended plural forms.
 * First parameter is the singular form of the string, second parameter is the
 * plural form, and third parameter is the number to check whether use singular,
 * plural or a specific language form.
 */
#   define _n(Msgid1, Msgid2, N) dngettext(PACKAGE, Msgid1, Msgid2, N)

/**
 * Marks the Msgid to be translated.
 * Used when _(Msgid) can't be used, for example, in array initializations.
 */
#   define gettext_noop(Msgid) Msgid

/**
 * Short form of gettext_noop(Msgid).
 * You must use it instead of gettext_noop(Msgid).
 */
#   define N_(Msgid) gettext_noop(Msgid)

#else
/* If NLS was disabled through the configure --disable-nls option, the macros
 * above are defined so they are substituted by the string to translate.
 * As seen in GNU gettext.h file, the casts to 'const char *' serve the purpose
 * of producing warnings for invalid uses of the value returned from these
 * functions.
 */
#   define _(Msgid) ((const char *) (Msgid))
#   define _n(Msgid1, Msgid2, N) \
        ((N) == 1 ? (const char *) (Msgid1) : (const char *) (Msgid2))
#   define N_(Msgid) Msgid

#endif

namespace lusi {
namespace util {

/**
 * Binds LUSI domain to the directory where LUSI locales are installed.
 * This method must be called in applications using LUSI before using other
 * resources provided by the library.
 * The directory used is $datadir/locale.
 */
void bindLusiTextDomain();

}
}

#endif
