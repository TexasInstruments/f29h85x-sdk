import{r as t,h as i,g as s}from"./p-ce1dc307.js";import"./p-98813443.js";import{w as e}from"./p-a3423d61.js";const n="ti-accordion .ti-accordion-button{color:#007c8c;cursor:pointer;float:none;margin-bottom:8px;text-align:right}ti-accordion .ti-accordion-button:hover{text-decoration:underline}ti-expansion-panel.ti-expansion-panel-expanded+ti-expansion-panel.ti-expansion-panel-expanded{border-top:none}";let o=class{constructor(i){t(this,i);this.EXPANSION_PANEL_NODENAME="TI-EXPANSION-PANEL";this._expandedCount=0;this.expansionPanels=[];this.autoCollapse=false;this.autoScroll=false;this.collapseAllLabel=o.DEFAULT_COLLAPSE_ALL_LABEL;this.expandAllLabel=o.DEFAULT_EXPAND_ALL_LABEL}componentWillLoad(){this.expansionPanels=[];Array.from(this.hostElement.children).forEach((t=>{if(t.nodeName===this.EXPANSION_PANEL_NODENAME){this.expansionPanels.push(t)}}));if(this.expansionPanels.length===0){return}if(this.autoCollapse){let t=false;this.expansionPanels.forEach((i=>{if(t){i.isExpanded=false}else if(i.isExpanded){t=true}}));return}this.expansionPanels.forEach((t=>{if(t.isExpanded){this._expandedCount++}}));this._updateExpandAllState()}handleExpansionPanelExpand(t){const i=t.target;if(!i||this.expansionPanels.indexOf(i)===-1){return}if(this.autoCollapse&&i&&i.isExpanded){this.expansionPanels.forEach((t=>{if(i!==t){t.isExpanded=false}else if(this.autoScroll){e(250).then((()=>{if(i.getBoundingClientRect().top<0){i.scrollIntoView({block:"start",inline:"nearest",behavior:"smooth"})}}))}}))}else if(i){if(i.isExpanded){this._expandedCount++}else{this._expandedCount--}}this._updateExpandAllState()}async toggle(){const t=this.action===1;this.action=t?0:1;this.expansionPanels.forEach((function(i){i.isExpanded=t}))}_updateExpandAllState(){if(this._expandedCount>this.expansionPanels.length/2){this.action=0}else{this.action=1}}render(){return[i("div",{class:"ti-accordion-button"},!this.autoCollapse&&i("span",{onClick:()=>this.toggle()},this.action===1?this.expandAllLabel:this.collapseAllLabel)),i("slot",null)]}get hostElement(){return s(this)}};o.DEFAULT_COLLAPSE_ALL_LABEL="Collapse all";o.DEFAULT_EXPAND_ALL_LABEL="Expand all";o.style=n;export{o as ti_accordion};
//# sourceMappingURL=p-5294c6fe.entry.js.map