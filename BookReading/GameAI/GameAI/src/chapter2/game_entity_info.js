/**
 * Created by guodong on 12/9/15.
 */

var EntityHelper =
{
    EntityID : {
        kMiner_Bob  : 1,
        kElsa       : 2,
    },

    GetEntityNameMap : function ()
    {
        if(!this._entity_name_map)
        {
            this._entity_name_map = {}

            this._entity_name_map[this.EntityID.kMiner_Bob ] = "Bob "
            this._entity_name_map[this.EntityID.kElsa      ] = "Elsa"
        }
        return this._entity_name_map
    },

    GetEntityName : function (entity_id)
    {
        return this.GetEntityNameMap()[entity_id] || "UNKNOWN_entity"
    },

    Location : {
        kInvalid    :0,
        kShack      :1,
        kGoldmine   :2,
        kBank       :3,
        kSaloon     :4,
        kBathroom   :5,
    },
    GetLocationNameMap : function () {
        if(!this._location_name_map)
        {
            this._location_name_map = {}
            this._location_name_map[this.Location.kInvalid  ] = "INVALID_location"
            this._location_name_map[this.Location.kShack    ] = "Shack           "
            this._location_name_map[this.Location.kGoldmine ] = "Goldmine        "
            this._location_name_map[this.Location.kBank     ] = "Bank            "
            this._location_name_map[this.Location.kSaloon   ] = "Saloon          "
            this._location_name_map[this.Location.kBathroom ] = "Bathroom        "
        }
        return this._location_name_map
    },
    GetLocationName : function (location_type)
    {
        return this.GetLocationNameMap()[location_type] || "UNKNOWN_location"
    },

    MsgType : {
        kMsg_Invalid            : 0,
        kMsg_HiHoneyImHome      : 1,
        kMsg_StewReady          : 2,
        kMsg_HiHoneyImAway      : 3,
        kMsg_HiHoneyImHungry    : 4,
    },
    GetMsgStrMap : function ()
    {
        if(!this._msg_str_map)
        {
            this._msg_str_map = {}
            this._msg_str_map[this.MsgType.kMsg_Invalid        ] = "MSG_INVALID        "
            this._msg_str_map[this.MsgType.kMsg_HiHoneyImHome  ] = "MSG_HiHoneyImHome  "
            this._msg_str_map[this.MsgType.kMsg_StewReady      ] = "MSG_StewReady      "
            this._msg_str_map[this.MsgType.kMsg_HiHoneyImAway  ] = "Msg_HiHoneyImAway  "
            this._msg_str_map[this.MsgType.kMsg_HiHoneyImHungry] = "Msg_HiHoneyImHungry"
        }
        return this._msg_str_map
    },
    GetMsgStr : function (msg_type)
    {
        return this.GetMsgStrMap()[msg_type] || "UNKNOWN_MSG"
    }
}