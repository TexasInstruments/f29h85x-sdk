import{r as s,g as t}from"./p-5bb37414.js";import{Usb2anyUartCodec as c}from"../gc-codec-usb2any-uart/lib/Usb2anyUartCodec";import{c as a}from"./p-0c6e1a4c.js";let e=class{constructor(t){s(this,t);this.parity="none";this.bitDirection="lsb";this.characterLength=8;this.baudRate=9600;this.stopBits=1;this.optional=false}connectedCallback(){this.impl=new c(a(this.el))}disconnectedCallback(){this.impl.dispose()}get el(){return t(this)}};export{e as gc_codec_usb2any_uart};
//# sourceMappingURL=p-fd0a7b6d.entry.js.map