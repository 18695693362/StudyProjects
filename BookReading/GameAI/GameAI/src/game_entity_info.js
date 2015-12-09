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

            this._entity_name_map[this.EntityID.kMiner_Bob ] = "Bob"
            this._entity_name_map[this.EntityID.kElsa      ] = "Elsa"
        }
        return this._entity_name_map
    },

    GetEntityName : function (entity_id)
    {
        return this._entity_name_map[entity_id] || "UNKNOWN"
    },

    Location : {
        kInvalid    :0,
        kShack      :1,
        kGoldmine   :2,
        kBank       :3,
        kSaloon     :4
    },
    GetLocationNameMap : function () {
        if(!this._location_name_map)
        {
            this._location_name_map = {}
            this._location_name_map[this.Location.kInvalid  ] = "INVALID "
            this._location_name_map[this.Location.kShack    ] = "Shack   "
            this._location_name_map[this.Location.kGoldmine ] = "Goldmine"
            this._location_name_map[this.Location.kBank     ] = "Bank    "
            this._location_name_map[this.Location.kSaloon   ] = "Saloon  "
        }
        return this._location_name_map
    },
    GetLocationName : function (location_type)
    {
        return this._entity_name_map[location_type] || "UNKNOWN"
    }
}