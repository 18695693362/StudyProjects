var skins;
(function (skins) {
    var ButtonSkin = (function (_super) {
        __extends(ButtonSkin, _super);
        function ButtonSkin() {
            _super.call(this);
            this.__s = egret.gui.setProperties;
            this.__s(this, ["height", "width"], [300, 400]);
            this.elementsContent = [this.__4_i(), this.labelDisplay_i()];
            this.states = [
                new egret.gui.State("up", []),
                new egret.gui.State("down", [
                    new egret.gui.SetProperty("__4", "source", "custom_down")
                ]),
                new egret.gui.State("disabled", [])
            ];
        }
        var d = __define,c=ButtonSkin;p=c.prototype;
        d(p, "skinParts"
            ,function () {
                return ButtonSkin._skinParts;
            }
        );
        p.labelDisplay_i = function () {
            var t = new egret.gui.Label();
            this.labelDisplay = t;
            this.__s(t, ["bold", "bottom", "left", "right", "text", "textAlign", "textColor", "top", "verticalAlign"], [true, 133, 102, 103, "HelloWorld", "center", 0x2D5B08, 125, "middle"]);
            return t;
        };
        p.__4_i = function () {
            var t = new egret.gui.UIAsset();
            this.__4 = t;
            this.__s(t, ["scale9Grid", "source", "width", "x", "y"], [egret.gui.getScale9Grid("36,35,25,21"), "custom_normal", 245, 76, 102]);
            return t;
        };
        ButtonSkin._skinParts = ["labelDisplay"];
        return ButtonSkin;
    })(egret.gui.Skin);
    skins.ButtonSkin = ButtonSkin;
    egret.registerClass(ButtonSkin,"skins.ButtonSkin");
})(skins || (skins = {}));
