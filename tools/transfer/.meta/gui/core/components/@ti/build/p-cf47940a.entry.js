import{r as t,c as i,h as s,H as e,g as o}from"./p-ce1dc307.js";import{C as n}from"./p-83823d11.js";const h=":host{display:inline-block;cursor:pointer}:host .ti-column-sort-header-container{display:inline-flex;flex-wrap:nowrap}:host .ti-column-sort-header-container .ti-column-sort-header-label+svg{margin-left:6px}:host .ti-column-sort-header-container svg{min-width:18px;min-height:18px;text-align:center;vertical-align:middle;padding-bottom:2px;fill:#999999;box-sizing:content-box}:host(.ti-column-sort-header-active) .ti-column-sort-header-container>svg{fill:#555555}";let r=class{constructor(s){t(this,s);this.tiColumnSortChange=i(this,"tiColumnSortChange",7);this.disabled=false;this.firstSortDirection=n.up;this.sortDirection=n.none}onClick(){if(!this.disabled){this.toggleSortDirection().then((()=>{this.tiColumnSortChange.emit({sortColumn:this.sortColumn,sortDirection:this.sortDirection,sortType:this.sortType})}))}}onKeydown(t){if(!this.disabled&&t.keyCode===32){t.preventDefault();this.toggleSortDirection().then((()=>{this.tiColumnSortChange.emit({sortColumn:this.sortColumn,sortDirection:this.sortDirection})}))}}async toggleSortDirection(){if(this.sortDirection===n.up){this.sortDirection=n.down}else if(this.sortDirection===n.down||this.firstSortDirection===n.up){this.sortDirection=n.up}else{this.sortDirection=n.down}}async setSortDirectionDown(){this.sortDirection=n.down}async setSortDirectionNone(){this.sortDirection=n.none}async setSortDirectionUp(){this.sortDirection=n.up}_getIconSvg(){if(this.sortDirection===n.up){return s("svg",{viewBox:"0 0 192 192",width:"18",height:"18"},s("path",{d:"M32 96l11.28 11.28L88 62.64V160h16V62.64l44.64 44.72L160 96 96 32z"}))}else if(this.sortDirection===n.down){return s("svg",{viewBox:"0 0 192 192",width:"18",height:"18"},s("path",{d:"M96 160l64-64-11.36-11.36L104 129.36V32H88v97.36L43.28 84.72 32 96z"}))}else{return s("svg",{viewBox:"0 0 192 192",width:"18",height:"18"},s("path",{d:"M144.905 160.134V62.797l28.279 28.279 11.383-11.384-47.669-47.668L89.2 79.721l11.384 11.384 28.308-28.308v97.337h16.013zM63.137 32.024v97.337l28.279-28.279 11.384 11.384-47.669 47.668-47.698-47.697 11.383-11.383 28.308 28.307V32.024h16.013z"}))}}render(){return s(e,{tabindex:!this.disabled&&"0",class:this.sortDirection!==n.none&&"ti-column-sort-header-active"},s("div",{class:"ti-column-sort-header-container",id:"sort_col_"+this.sortColumn},this.hostElement.textContent.trim().length>0?s("div",{class:"ti-column-sort-header-label"},s("slot",null)):s("slot",null),!this.disabled&&this._getIconSvg()))}get hostElement(){return o(this)}};r.SORT_DIRECTION={down:"down",none:"none",up:"up"};r.style=h;export{r as ti_column_sort_header};
//# sourceMappingURL=p-cf47940a.entry.js.map