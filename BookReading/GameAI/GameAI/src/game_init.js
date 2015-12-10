var _custom_js_files = []
_custom_js_files.push([
    "src/state.js",
    "src/utility.js",
    "src/game_entity_info.js",

    "src/game_entity.js",
    "src/miner.js",
    "src/miner_state.js"
])

for(var i=0; i<_custom_js_files.length; i++)
{
    require(_custom_js_files[i])
}