/**
 *
 * @author 
 *
 */
module game { 
    export class IconButton extends egret.gui.Button { 
        public constructor() { 
            super();
        }
        public iconDisplay: egret.gui.UIAsset;
        private _icon: any;
        public get icon(): any
        {
            return this._icon;
        }
        public set icon(value: any)
        {
            if(value == this._icon)
            {
                return;
            }
            this._icon = value;
            if(this.iconDisplay)
            { 
                this.iconDisplay.source = value;
            }
        }
        public partAdded(partName: string,instance: any): void { 
            super.partAdded(partName,instance);
            if(instance == this.iconDisplay)
            {
                this.iconDisplay.source = this._icon;
            }
        }
    }
}
