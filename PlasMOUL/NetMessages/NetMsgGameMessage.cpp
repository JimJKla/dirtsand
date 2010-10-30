/******************************************************************************
 * This file is part of dirtsand.                                             *
 *                                                                            *
 * dirtsand is free software: you can redistribute it and/or modify           *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation, either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * dirtsand is distributed in the hope that it will be useful,                *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with dirtsand.  If not, see <http://www.gnu.org/licenses/>.          *
 ******************************************************************************/

#include "NetMsgGameMessage.h"
#include "factory.h"

void MOUL::NetMsgGameMessage::read(DS::Stream* stream)
{
    NetMessage::read(stream);

    NetMsgStream msgStream;
    msgStream.read(stream);
    m_compression = msgStream.m_compression;
    m_message = Factory::Read<Message>(&msgStream.m_stream);

    if (stream->readBool())
        m_deliveryTime.read(stream);
}

void MOUL::NetMsgGameMessage::write(DS::Stream* stream)
{
    NetMessage::write(stream);

    NetMsgStream msgStream(m_compression);
    Factory::WriteCreatable(&msgStream.m_stream, m_message);
    msgStream.write(stream);

    if (!m_deliveryTime.isNull()) {
        stream->writeBool(true);
        m_deliveryTime.write(stream);
    } else {
        stream->writeBool(false);
    }
}