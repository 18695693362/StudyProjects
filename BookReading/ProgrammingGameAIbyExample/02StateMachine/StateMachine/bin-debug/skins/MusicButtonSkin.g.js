var skins;
(function (skins) {
    var MusicButtonSkin = (function (_super) {
        __extends(MusicButtonSkin, _super);
        function MusicButtonSkin() {
            _super.call(this);
            this.__s = egret.gui.setProperties;
            this.__s(this, ["height", "width"], [300, 400]);
            this.elementsContent = [this.__7_i()];
            this.states = [
                new egret.gui.State("up", [
                    new egret.gui.SetProperty("__7", "source", "music_normal")
                ]),
                new egret.gui.State("down", []),
                new egret.gui.State("disabled", []),
                new egret.gui.State("upAndSelected", [
                    new egret.gui.SetProperty("__7", "source", "music_non_normal")
                ]),
                new egret.gui.State("downAndSelected", [
                    new egret.gui.SetProperty("__7", "source", "music_non_down")
                ]),
                new egret.gui.State("disabledAndSelected", [])
            ];
        }
        var d = __define,c=MusicButtonSkin;p=c.prototype;
        p.__7_i = function () {
            var t = new egret.gui.UIAsset();
            this.__7 = t;
            this.__s(t, ["source", "x", "y"], ["music_down", 88, 108]);
            return t;
        };
        return MusicButtonSkin;
    })(egret.gui.Skin);
    skins.MusicButtonSkin = MusicButtonSkin;
    egret.registerClass(MusicButtonSkin,"skins.MusicButtonSkin");
})(skins || (skins = {}));
