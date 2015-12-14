var MM = MM || {}

MM._js_cache = {}
MM._custom_js_files = []
Array.prototype.push.apply(MM._custom_js_files,[
    "src/utility.js",
    "src/state.js",
    "src/state_machine.js",

    "src/resource.js",

    "src/game_entity_info.js",
    "src/game_entity.js",
    "src/miner.js",
    "src/miner_state.js",

    "src/app.js",
])

MM.LoadJs = function (js_path,cb)
{
    var l_cb = function (err) {
        if (err)
        {
            throw new Error(err);
        }
        else
        {
            MM._js_cache[js_path] = true
            if(cb)cb()
        }
    }

    if(MM._js_cache[js_path])
        return l_cb(null);
    cc.loader._createScript(js_path, false, l_cb);
}
MM.LoadAllJs = function (step_cb, completed_cb)
{
    var finished_count  = 0
    var total_count     = MM._custom_js_files.length

    var l_step_cb = function (total, idx)
    {
        finished_count++

        if(step_cb)
        {
            step_cb(total_count,idx)
        }
        if(finished_count>=total_count)
        {
            if(completed_cb)completed_cb()
        }
    }

    for(var i=0; i<MM._custom_js_files.length; i++)
    {
        MM.LoadJs(MM._custom_js_files[i],l_step_cb)
    }
}

MM.Start = function () {
    MM.LoadAllJs(null, function () {
        cc.LoaderScene.preload(g_resources, function () {
            cc.director.runScene(new HelloWorldScene());
        }, this);
    })
}()