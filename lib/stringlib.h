/***********************************************************
* This file is part of glyr
* + a commnadline tool and library to download various sort of musicrelated metadata.
* + Copyright (C) [2011]  [Christopher Pahl]
* + Hosted at: https://github.com/sahib/glyr
*
* glyr is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* glyr is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with glyr. If not, see <http://www.gnu.org/licenses/>.
**************************************************************/

#ifndef STRINGOP_H
#define STRINGOP_H

#include <glib.h>

/* Glyr's internal unicode stringlib - You're free to use it. */

/* Cheap, but well working macro */
#define nextTag(PTR) while(PTR[0] && *PTR++ != '>')

/* Compute levenshtein distance of 'string' to 'other' */
gsize levenshtein_strcmp(const gchar * string, const gchar * other);

/* Same as above, but converts to lowercase before */
gsize levenshtein_strcasecmp(const gchar * sstring, const gchar * other);

/* Replaces 'subs' with 'with' in string, returns newly allocated string or NULL */
gchar * strreplace(const gchar * string, const gchar * subs, const gchar * with);

/* Converts charset of 'string' from charset 'from' to charset 'to', number of bytes saved in new_size (can be NULL) */
gchar * convert_charset(const gchar * string, gchar * from, gchar * to, gsize * new_size);

/* Replaces HTML-unicode strings like &ouml; with their UTF-8 bytes */
gchar * strip_html_unicode(const gchar * string);

/* Removes trailing '\n' or '\r\n' in a string */
void chomp_breakline(gchar * string);

/* Pass a string to input, and an allocated buffer to output */
void trim_copy(gchar *input, gchar *output);

/* Same as above, but does trim inplace */
void trim_inplace(gchar *s);

/* Same as above, but returns new pointer (inplace) */
gchar * trim_nocopy(gchar *s);

/* Copies the value from begin to end, returns newly allocated buffer */
gchar * copy_value(const gchar * begin, const gchar * end);

/* Iterates over string, always returning string to the next 'delim' offset and len != 0!  */
gchar * get_next_word(const gchar * string, const gchar * delim, gsize * offset, gsize len);

/* Removes everything between 'start' and 'end', works inplace  */
gsize remove_tags_from_string(gchar * string, gint length, gchar start, gchar end);

/* Unescapes HTML numeric unicode entities to normal UTF8 strings */
gchar * unescape_html_UTF8(const gchar *data);

/* Puts artist, album title in the string URL where it is %artist%,%album%,%title% */
gchar * prepare_url(const gchar * URL, const gchar * artist, const gchar * album, const gchar * title);

/* Runs many of the above funtions to make lyrics beautier */
gchar * beautify_lyrics(const gchar * lyrics);

#endif
