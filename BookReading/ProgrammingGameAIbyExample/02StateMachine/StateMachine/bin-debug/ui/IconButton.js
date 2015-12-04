/**
 *
 * @author
 *
 */
var game;
(function (game) {
    var IconButton = (function (_super) {
        __extends(IconButton, _super);
        function IconButton() {
            _super.call(this);
        }
        var d = __define,c=IconButton;p=c.prototype;
        d(p, "icon"
            ,function () {
                return this._icon;
            }
            ,function (value) {
                if (value == this._icon) {
                    return;
                }
                this._icon = value;
                if (this.iconDisplay) {
                    this.iconDisplay.source = value;
                }
            }
        );
        p.partAdded = function (partName, instance) {
            _super.prototype.partAdded.call(this, partName, instance);
            if (instance == this.iconDisplay) {
                this.iconDisplay.source = this._icon;
            }
        };
        return IconButton;
    })(egret.gui.Button);
    game.IconButton = IconButton;
    egret.registerClass(IconButton,"game.IconButton");
})(game || (game = {}));
