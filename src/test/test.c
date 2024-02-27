#include "utest.h"
#include <conclave-room-client/client_serialize.h>
#include <conclave-room-serialize/client_in.h>
#include <flood/in_stream.h>

UTEST(RoomClientSerialize, verify)
{
    const uint8_t EXPECTED_LEADER_INDEX = 0xff;

    uint8_t octets[] = {
        clvRoomSerializeCmdPing,
        0x00, // Term
        0x4A, // Term (lower)
        0x00, // Number of client infos that follows
        EXPECTED_LEADER_INDEX, // Leader index
    };

    struct FldInStream inStream;
    fldInStreamInit(&inStream, octets, sizeof(octets));

    ClvRoomClientSerialize clientSerialize;

    Clog log;
    log.config = &g_clog;
    log.constantPrefix = "test";
    clvSerializeRoomClientInit(&clientSerialize, log);

    int error = clvSerializeRoomClientRead(&clientSerialize, &inStream);
    ASSERT_EQ(0, error);

    ASSERT_EQ(0x4A, clientSerialize.state.term);
    //ASSERT_EQ(0, clientSerialize.state..memberCount);
    ASSERT_EQ(EXPECTED_LEADER_INDEX, clientSerialize.state.leader);
}
