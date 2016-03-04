#ifndef MPLAYER2OUTPUTFORMAT_H
#define MPLAYER2OUTPUTFORMAT_H

/***************************************************************************
 *   Copyright (C) 2007-2009 Sergio Pistone (sergio_pistone@yahoo.com.ar)  *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,      *
 *   Boston, MA 02110-1301, USA.                                           *
 ***************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "../outputformat.h"
#include "../../core/subtitleiterator.h"

namespace SubtitleComposer {
class MPlayer2OutputFormat : public OutputFormat
{
	friend class FormatManager;

protected:
	virtual QString dumpSubtitles(const Subtitle &subtitle, bool primary) const
	{
		QString ret;

		for(SubtitleIterator it(subtitle); it.current(); ++it) {
			const SubtitleLine *line = it.current();

			const SString &text = primary ? line->primaryText() : line->secondaryText();

			ret += m_lineBuilder.arg((long)((line->showTime().toMillis() / 100.0) + 0.5))
					.arg((long)((line->hideTime().toMillis() / 100.0) + 0.5))
					.arg(text.string().replace('\n', '|'));
		}
		return ret;
	}

	MPlayer2OutputFormat() :
		OutputFormat("MPlayer2", QStringList("mpl")),
		m_lineBuilder("[%1][%2]%3\n")
	{}

	const QString m_lineBuilder;
};
}

#endif
