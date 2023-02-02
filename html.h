//***********************************************************************************************************************************************************************************************************************************
//WEB PAGES
//***********************************************************************************************************************************************************************************************************************************

const char index_html[] PROGMEM = R"rawliteral(<html>

<head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
        body,
        html {
            background-color: #000;
            margin: 0;
            padding: 0;
            text-align: center;
            color: #999;
            display: flex;
            flex-direction: column;
        }
        
        select,
        button {
            background-color: #000;
            color: #999;
            border: solid 1px #999;
        }
        
        button {
            font-size: large;
            margin-top: 10px;
        }
        
        #image,
        #settings {
            overflow: hidden;
            position: relative;
        }
        
        #therm table {
            position: absolute;
            bottom: 0;
            left: 0;
            width: 100%;
            height: 36px;
        }
        
        #imageContainer {
            display: inline-block;
            margin-left: auto;
            margin-right: auto;
            position: relative;
            overflow: hidden;
            width: 100%;
            padding-top: calc(3 / 4 * 100%);
        }
        
        #canvas,
        #colorImage {
            position: absolute;
            top: 0;
            left: 0;
            width: 100%;
            height: 100%;
            opacity: .6;
        }
        
        #colorImage {
            transform: scale(1);
        }
        
        #status {
            text-align: center;
            font-family: 'Courier New', Courier, monospace;
        }
        
        .flex {
            display: flex;
            justify-content: space-between;
        }
        
        .flex-1 {
            flex: 1;
        }
        
        .flex-c {
            flex-direction: column;
        }
        
        .center {
            text-align: center;
        }
        
        #therm {
            border-bottom: solid 1px #ddd;
            padding-bottom: 2px;
            height: 36px;
            position: absolute;
            width: 100%;
            bottom: 18px;
            left: 0;
        }
        
        #rangeSetting {
            border-bottom: solid 1px #ddd;
            padding-bottom: 2px;
            margin-bottom: 5px;
        }
        
        table {
            width: 100%;
        }
        
        #rangeTable {
            height: 10px;
        }
        
        label {
            display: flex;
            flex-direction: column;
            flex: 1;
        }
        
        label input {
            align-self: center;
            width: 100%;
        }
        
        #minTherm {
            color: blue;
        }
        
        #centerTherm {
            color: #ddd;
        }
        
        #maxTherm {
            color: red;
        }
        
        #marker {
            position: absolute;
            color: #fff;
            text-shadow: 0 0 black;
            font-size: 30px;
            opacity: 0;
        }
        
        #status {
            margin-top: 50px;
        }

        .hide {
            display: none;
        }
        
        @media (orientation: landscape) {
            body {
                flex-direction: row;
            }
            #settings {
                flex: 1;
            }
            #image {
                width: calc(4 / 3 * 100vh);
            }
        }
    </style>
    <script>
        /*! dom-to-image 10-06-2017 */
        !function(a){"use strict";function b(a,b){function c(a){return b.bgcolor&&(a.style.backgroundColor=b.bgcolor),b.width&&(a.style.width=b.width+"px"),b.height&&(a.style.height=b.height+"px"),b.style&&Object.keys(b.style).forEach(function(c){a.style[c]=b.style[c]}),a}return b=b||{},g(b),Promise.resolve(a).then(function(a){return i(a,b.filter,!0)}).then(j).then(k).then(c).then(function(c){return l(c,b.width||q.width(a),b.height||q.height(a))})}function c(a,b){return h(a,b||{}).then(function(b){return b.getContext("2d").getImageData(0,0,q.width(a),q.height(a)).data})}function d(a,b){return h(a,b||{}).then(function(a){return a.toDataURL()})}function e(a,b){return b=b||{},h(a,b).then(function(a){return a.toDataURL("image/jpeg",b.quality||1)})}function f(a,b){return h(a,b||{}).then(q.canvasToBlob)}function g(a){"undefined"==typeof a.imagePlaceholder?v.impl.options.imagePlaceholder=u.imagePlaceholder:v.impl.options.imagePlaceholder=a.imagePlaceholder,"undefined"==typeof a.cacheBust?v.impl.options.cacheBust=u.cacheBust:v.impl.options.cacheBust=a.cacheBust}function h(a,c){function d(a){var b=document.createElement("canvas");if(b.width=c.width||q.width(a),b.height=c.height||q.height(a),c.bgcolor){var d=b.getContext("2d");d.fillStyle=c.bgcolor,d.fillRect(0,0,b.width,b.height)}return b}return b(a,c).then(q.makeImage).then(q.delay(100)).then(function(b){var c=d(a);return c.getContext("2d").drawImage(b,0,0),c})}function i(a,b,c){function d(a){return a instanceof HTMLCanvasElement?q.makeImage(a.toDataURL()):a.cloneNode(!1)}function e(a,b,c){function d(a,b,c){var d=Promise.resolve();return b.forEach(function(b){d=d.then(function(){return i(b,c)}).then(function(b){b&&a.appendChild(b)})}),d}var e=a.childNodes;return 0===e.length?Promise.resolve(b):d(b,q.asArray(e),c).then(function(){return b})}function f(a,b){function c(){function c(a,b){function c(a,b){q.asArray(a).forEach(function(c){b.setProperty(c,a.getPropertyValue(c),a.getPropertyPriority(c))})}a.cssText?b.cssText=a.cssText:c(a,b)}c(window.getComputedStyle(a),b.style)}function d(){function c(c){function d(a,b,c){function d(a){var b=a.getPropertyValue("content");return a.cssText+" content: "+b+";"}function e(a){function b(b){return b+": "+a.getPropertyValue(b)+(a.getPropertyPriority(b)?" !important":"")}return q.asArray(a).map(b).join("; ")+";"}var f="."+a+":"+b,g=c.cssText?d(c):e(c);return document.createTextNode(f+"{"+g+"}")}var e=window.getComputedStyle(a,c),f=e.getPropertyValue("content");if(""!==f&&"none"!==f){var g=q.uid();b.className=b.className+" "+g;var h=document.createElement("style");h.appendChild(d(g,c,e)),b.appendChild(h)}}[":before",":after"].forEach(function(a){c(a)})}function e(){a instanceof HTMLTextAreaElement&&(b.innerHTML=a.value),a instanceof HTMLInputElement&&b.setAttribute("value",a.value)}function f(){b instanceof SVGElement&&(b.setAttribute("xmlns","http://www.w3.org/2000/svg"),b instanceof SVGRectElement&&["width","height"].forEach(function(a){var c=b.getAttribute(a);c&&b.style.setProperty(a,c)}))}return b instanceof Element?Promise.resolve().then(c).then(d).then(e).then(f).then(function(){return b}):b}return c||!b||b(a)?Promise.resolve(a).then(d).then(function(c){return e(a,c,b)}).then(function(b){return f(a,b)}):Promise.resolve()}function j(a){return s.resolveAll().then(function(b){var c=document.createElement("style");return a.appendChild(c),c.appendChild(document.createTextNode(b)),a})}function k(a){return t.inlineAll(a).then(function(){return a})}function l(a,b,c){return Promise.resolve(a).then(function(a){return a.setAttribute("xmlns","http://www.w3.org/1999/xhtml"),(new XMLSerializer).serializeToString(a)}).then(q.escapeXhtml).then(function(a){return'<foreignObject x="0" y="0" width="100%" height="100%">'+a+"</foreignObject>"}).then(function(a){return'<svg xmlns="http://www.w3.org/2000/svg" width="'+b+'" height="'+c+'">'+a+"</svg>"}).then(function(a){return"data:image/svg+xml;charset=utf-8,"+a})}function m(){function a(){var a="application/font-woff",b="image/jpeg";return{woff:a,woff2:a,ttf:"application/font-truetype",eot:"application/vnd.ms-fontobject",png:"image/png",jpg:b,jpeg:b,gif:"image/gif",tiff:"image/tiff",svg:"image/svg+xml"}}function b(a){var b=/\.([^\.\/]*?)$/g.exec(a);return b?b[1]:""}function c(c){var d=b(c).toLowerCase();return a()[d]||""}function d(a){return a.search(/^(data:)/)!==-1}function e(a){return new Promise(function(b){for(var c=window.atob(a.toDataURL().split(",")[1]),d=c.length,e=new Uint8Array(d),f=0;f<d;f++)e[f]=c.charCodeAt(f);b(new Blob([e],{type:"image/png"}))})}function f(a){return a.toBlob?new Promise(function(b){a.toBlob(b)}):e(a)}function g(a,b){var c=document.implementation.createHTMLDocument(),d=c.createElement("base");c.head.appendChild(d);var e=c.createElement("a");return c.body.appendChild(e),d.href=b,e.href=a,e.href}function h(){var a=0;return function(){function b(){return("0000"+(Math.random()*Math.pow(36,4)<<0).toString(36)).slice(-4)}return"u"+b()+a++}}function i(a){return new Promise(function(b,c){var d=new Image;d.onload=function(){b(d)},d.onerror=c,d.src=a})}function j(a){var b=3e4;return v.impl.options.cacheBust&&(a+=(/\?/.test(a)?"&":"?")+(new Date).getTime()),new Promise(function(c){function d(){if(4===g.readyState){if(200!==g.status)return void(h?c(h):f("cannot fetch resource: "+a+", status: "+g.status));var b=new FileReader;b.onloadend=function(){var a=b.result.split(/,/)[1];c(a)},b.readAsDataURL(g.response)}}function e(){h?c(h):f("timeout of "+b+"ms occured while fetching resource: "+a)}function f(a){console.error(a),c("")}var g=new XMLHttpRequest;g.onreadystatechange=d,g.ontimeout=e,g.responseType="blob",g.timeout=b,g.open("GET",a,!0),g.send();var h;if(v.impl.options.imagePlaceholder){var i=v.impl.options.imagePlaceholder.split(/,/);i&&i[1]&&(h=i[1])}})}function k(a,b){return"data:"+b+";base64,"+a}function l(a){return a.replace(/([.*+?^${}()|\[\]\/\\])/g,"\\$1")}function m(a){return function(b){return new Promise(function(c){setTimeout(function(){c(b)},a)})}}function n(a){for(var b=[],c=a.length,d=0;d<c;d++)b.push(a[d]);return b}function o(a){return a.replace(/#/g,"%23").replace(/\n/g,"%0A")}function p(a){var b=r(a,"border-left-width"),c=r(a,"border-right-width");return a.scrollWidth+b+c}function q(a){var b=r(a,"border-top-width"),c=r(a,"border-bottom-width");return a.scrollHeight+b+c}function r(a,b){var c=window.getComputedStyle(a).getPropertyValue(b);return parseFloat(c.replace("px",""))}return{escape:l,parseExtension:b,mimeType:c,dataAsUrl:k,isDataUrl:d,canvasToBlob:f,resolveUrl:g,getAndEncode:j,uid:h(),delay:m,asArray:n,escapeXhtml:o,makeImage:i,width:p,height:q}}function n(){function a(a){return a.search(e)!==-1}function b(a){for(var b,c=[];null!==(b=e.exec(a));)c.push(b[1]);return c.filter(function(a){return!q.isDataUrl(a)})}function c(a,b,c,d){function e(a){return new RegExp("(url\\(['\"]?)("+q.escape(a)+")(['\"]?\\))","g")}return Promise.resolve(b).then(function(a){return c?q.resolveUrl(a,c):a}).then(d||q.getAndEncode).then(function(a){return q.dataAsUrl(a,q.mimeType(b))}).then(function(c){return a.replace(e(b),"$1"+c+"$3")})}function d(d,e,f){function g(){return!a(d)}return g()?Promise.resolve(d):Promise.resolve(d).then(b).then(function(a){var b=Promise.resolve(d);return a.forEach(function(a){b=b.then(function(b){return c(b,a,e,f)})}),b})}var e=/url\(['"]?([^'"]+?)['"]?\)/g;return{inlineAll:d,shouldProcess:a,impl:{readUrls:b,inline:c}}}function o(){function a(){return b(document).then(function(a){return Promise.all(a.map(function(a){return a.resolve()}))}).then(function(a){return a.join("\n")})}function b(){function a(a){return a.filter(function(a){return a.type===CSSRule.FONT_FACE_RULE}).filter(function(a){return r.shouldProcess(a.style.getPropertyValue("src"))})}function b(a){var b=[];return a.forEach(function(a){try{q.asArray(a.cssRules||[]).forEach(b.push.bind(b))}catch(c){console.log("Error while reading CSS rules from "+a.href,c.toString())}}),b}function c(a){return{resolve:function(){var b=(a.parentStyleSheet||{}).href;return r.inlineAll(a.cssText,b)},src:function(){return a.style.getPropertyValue("src")}}}return Promise.resolve(q.asArray(document.styleSheets)).then(b).then(a).then(function(a){return a.map(c)})}return{resolveAll:a,impl:{readAll:b}}}function p(){function a(a){function b(b){return q.isDataUrl(a.src)?Promise.resolve():Promise.resolve(a.src).then(b||q.getAndEncode).then(function(b){return q.dataAsUrl(b,q.mimeType(a.src))}).then(function(b){return new Promise(function(c,d){a.onload=c,a.onerror=d,a.src=b})})}return{inline:b}}function b(c){function d(a){var b=a.style.getPropertyValue("background");return b?r.inlineAll(b).then(function(b){a.style.setProperty("background",b,a.style.getPropertyPriority("background"))}).then(function(){return a}):Promise.resolve(a)}return c instanceof Element?d(c).then(function(){return c instanceof HTMLImageElement?a(c).inline():Promise.all(q.asArray(c.childNodes).map(function(a){return b(a)}))}):Promise.resolve(c)}return{inlineAll:b,impl:{newImage:a}}}var q=m(),r=n(),s=o(),t=p(),u={imagePlaceholder:void 0,cacheBust:!1},v={toSvg:b,toPng:d,toJpeg:e,toBlob:f,toPixelData:c,impl:{fontFaces:s,images:t,util:q,inliner:r,options:{}}};"undefined"!=typeof module?module.exports=v:a.domtoimage=v}(this);
    </script>
    <script>
        Color = function(hexOrObject) {
            var obj;
            if (hexOrObject instanceof Object) {
                obj = hexOrObject;
            } else {
                obj = LinearColorInterpolator.convertHexToRgb(hexOrObject);
            }
            this.r = obj.r;
            this.g = obj.g;
            this.b = obj.b;
            this.a = obj.a;
        }
        Color.prototype.asRgbCss = function() {
            return "rgba(" + this.r + ", " + this.g + ", " + this.b + ", " + this.a + ")";
        }

        var LinearColorInterpolator = {
            convertHexToRgb: function(hex) {
                match = hex.replace(/#/, '').match(/.{1,2}/g);
                return new Color({
                    r: parseInt(match[0], 16),
                    g: parseInt(match[1], 16),
                    b: parseInt(match[2], 16),
                    a: (hex.length > 7 ? parseInt(match[3], 16) : 255)
                });
            },
            findColorBetween: function(left, right, percentage) {
                newColor = {};
                components = ["r", "g", "b", "a"];
                for (var i = 0; i < components.length; i++) {
                    c = components[i];
                    newColor[c] = Math.round(left[c] + (right[c] - left[c]) * percentage / 100);
                }
                return new Color(newColor);
            }
        }
    </script>
</head>

<body>
    <div id="image">
        <div id="imageContainer">
            <img id="colorImage">
            <canvas id="canvas"></canvas>
            <div id="marker">+</div>
        </div>
        <div id="therm">
            <table border="0" cellspacing="0" cellpadding="0">
                <tr id="valueTable">

                </tr>
                <tr id="rangeTable">

                </tr>
            </table>
        </div>
        <div class="center">
            <span id="meterValue"></span>
        </div>
    </div>
    <div id="settings">
        <div class="flex">
            <label id="minContainer"><span>Min <span id="minSetting"></span></span><input type="range" id="minValue"
                    min="-20" max="100" step="1" value="20" oninput="updateSettings()"></label>
            <label id="distanceContainer"><span>Min Distance <span id="distanceSetting"></span></span><input
                    type="range" id="distanceValue" min="0" max="15" step="1" value="5"
                    oninput="updateSettings()"></label>
            <label id="maxContainer"><span>Max <span id="maxSetting"></span></span><input type="range" id="maxValue"
                    min="-20" max="100" step="1" value="40" oninput="updateSettings()"></label>
        </div>
        <div class="flex">
            <label>Adaptive<input type="checkbox" id="adaptiveValue" onchange="updateSettings()"></label>
            <div class="flex flex-1 flex-c">
                <label>Palette<select id="paletteValue" onchange="updateSettings()"></select></label>
                <label><span>Opacity <span id="opacitySetting"></span></span><input type="range" id="opacityValue"
                        min="0" max="100" step="5" value="60" oninput="updateSettings()"></label>
            </div>
            <label>Average<input type="checkbox" id="avgValue" onchange="updateSettings()"></label>
        </div>
        <div class="center">
            <button onclick="captureTherm()">Capture</button>
            <button onclick="togglePosition()">Set position</button>
        </div>
        <div class="flex position hide">
            <label id="posXContainer"><span>Position X <span id="posX"></span></span><input type="range" id="posXValue"
                    min="-12.5" max="12.5" step="0.1" value="0" oninput="updateSettings()"></label>
        </div>
        <div class="flex position hide">
            <label id="posYContainer"><span>Position Y <span id="posY"></span></span><input type="range" id="posYValue"
                    min="-12.5" max="12.5" step="0.1" value="0" oninput="updateSettings()"></label>
        </div>
        <div class="flex position hide">
            <label id="posYContainer"><span>Zoom <span id="zoom"></span></span><input type="range" id="zoomValue"
                    min="0.5" max="2" step="0.01" value="1" oninput="updateSettings()"></label>
        </div>
        <div id="status">
            <span id="fps"></span><br>
            <span id="debugStatus"></span>
        </div>
        <div id="status">
            <span id="fps"></span><br>
            <span id="debugStatus"></span>
        </div>
    </div>
    <script>
        const host = window.location.hostname + "/ws";
        const sizeX = 32;
        const sizeY = 24;
        const multiplier = 20;
        let rangeMin = 20;
        let rangeMax = 40;
        let adaptiveRange = false;
        const palettes = [{
            name: "FLIR Transparent",
            stops: ["#00000000", "#20008C", "#CC0077", "#FFD700", "#FFFFFF"]
        }, {
            name: "FLIR",
            stops: ["#000000", "#20008C", "#CC0077", "#FFD700", "#FFFFFF"]
        }, {
            name: "BW Transparent",
            stops: ["#00000000", "#FFFFFF"]
        }, {
            name: "BW",
            stops: ["#000000", "#FFFFFF"]
        }, {
            name: "WB Transparent",
            stops: ["#FFFFFF00", "#000000"]
        }, {
            name: "WB",
            stops: ["#FFFFFF", "#000000"]
        }];
        let currentPalette = null;
        const paletteSelect = document.getElementById('paletteValue');
        if (paletteSelect.options.length != palettes.length) {
            palettes.forEach((pal, index) => {
                paletteSelect.options[index] = new Option(pal.name, index);
            });
        }

        let accumlator = [];
        let avg = true;
        let imageLoading = false;
        let metercoords = null;
        let mindistance = 10;

        let frameCount = 0;
        let opacity = 60;

        const image = document.getElementById('colorImage');
        image.width = sizeX * multiplier;
        image.height = sizeY * multiplier;

        const canvas = document.getElementById('canvas');
        canvas.addEventListener('click', setMeter);
        const marker = document.getElementById('marker');
        marker.addEventListener('click', () => {
            metercoords = null;
            marker.style.opacity = 0;
        });

        const socket = new WebSocket("ws://" + host);
        socket.binaryType = "arraybuffer";

        // Listen for messages
        socket.addEventListener("message", function(event) {
            if (event.data instanceof ArrayBuffer) {
                frameCount++;
                const therm = new Float32Array(new Uint8Array(event.data).slice(0, sizeX * sizeY * 4).buffer);
                if (avg) {
                    if (accumlator == null || accumlator.length != therm.length) {
                        accumlator = therm;
                    } else {
                        accumlator.forEach((elem, index) => {
                            accumlator[index] = Math.round(((elem + therm[index]) / 2) * 10) / 10;
                        });
                        drawCanvas(accumlator);
                    }
                } else {
                    drawCanvas(therm);
                }
                if (!imageLoading) {
                    imageLoading = true;
                    const blob = new Blob([new Uint8Array(event.data).slice(sizeX * sizeY * 4).buffer]);
                    const image = document.getElementById('colorImage');
                    const reader = new FileReader();
                    reader.onload = function(e) {
                        image.src = e.target.result;
                        imageLoading = false;
                    };
                    reader.readAsDataURL(blob);
                }
            } else {
                if (event.data.startsWith('STATUS:')) {
                    const status = event.data.replace('STATUS:', '');
                    document.getElementById('debugStatus').innerText = status;
                } else if (event.data.startsWith('SERIAL:')) {
                    console.info(event.data.replace('SERIAL:', ''));
                }
            }
        });

        function drawCanvas(therm) {
            if (therm == undefined) {
                therm = accumlator;
            }
            if (therm.length != sizeX * sizeY) {
                return;
            }
            const thermMin = Math.min(...therm);
            const thermMax = Math.max(...therm);
            const thermCenter = thermMin + ((thermMax - thermMin) / 2);
            let min = thermMin;
            let max = thermMax;
            if ((thermMax - thermMin) < mindistance) {
                min = Math.round((thermCenter - (mindistance / 2)) * 10) / 10;
                max = Math.round((thermCenter + (mindistance / 2)) * 10) / 10;
            }
            let meter = therm[(sizeY / 2) * sizeX + sizeX / 2];
            if (metercoords) {
                meter = therm[(metercoords.y) * sizeX + ((sizeX - 1) - metercoords.x)];
            }
            document.getElementById('meterValue').innerText = (metercoords != null ? 'Marker: ' : 'Center: ') + Math.round(meter * 10) / 10;
            if (adaptiveRange) {
                drawRangeTable(min, max);
            } else {
                drawRangeTable(rangeMin, rangeMax);
            }
            const canvas = document.getElementById('canvas');
            canvas.width = sizeX;
            canvas.height = sizeY;
            const image = document.getElementById('colorImage');
            const ctx = canvas.getContext('2d');
            const canvasWidth = sizeX;
            const canvasHeight = sizeY;
            ctx.clearRect(0, 0, canvasWidth, canvasHeight);
            const id = ctx.getImageData(0, 0, sizeX, sizeY);
            var pixels = id.data;

            let thermCount = 0;
            for (var y = 0; y < sizeY; y++) {
                for (var x = 0; x < sizeX; x++) {
                    const val = map(therm[thermCount], (adaptiveRange ? min : rangeMin), (adaptiveRange ? max : rangeMax), 0, 100);
                    const off = (y * id.width + ((sizeX - 1) - x)) * 4;
                    const color = getPaletteColor(val);
                    pixels[off] = color.r;
                    pixels[off + 1] = color.g;
                    pixels[off + 2] = color.b;
                    pixels[off + 3] = color.a;
                    thermCount++;
                }
            }
            ctx.putImageData(id, 0, 0, 0, 0, sizeX, sizeY);
        }

        function updateSettings() {
            avg = document.getElementById('avgValue').checked;
            adaptiveRange = document.getElementById('adaptiveValue').checked;

            if (currentPalette != palettes[parseInt(document.getElementById('paletteValue').value, 10)] || document.getElementById('rangeTable').innerHTML.trim() == '') {
                currentPalette = palettes[parseInt(document.getElementById('paletteValue').value, 10)];
                let rangeTable = '<td colspan="' + currentPalette.stops.length + '" style="background:linear-gradient(to right';
                currentPalette.stops.forEach((stop) => {
                    rangeTable += ',' + new Color(stop).asRgbCss();
                });
                rangeTable += ')"></td>';
                document.getElementById('rangeTable').innerHTML = rangeTable;
            }

            opacity = parseInt(document.getElementById('opacityValue').value, 10);
            document.getElementById('opacitySetting').innerText = opacity + "%";
            document.getElementById('canvas').style.opacity = opacity / 100;
            document.getElementById('rangeTable').style.opacity = opacity / 100;

            if (!adaptiveRange) {
                document.getElementById('distanceContainer').style.display = 'none';
                document.getElementById('minContainer').style.display = 'inline-block';
                document.getElementById('maxContainer').style.display = 'inline-block';

                rangeMin = parseInt(document.getElementById('minValue').value, 10);
                rangeMax = parseInt(document.getElementById('maxValue').value, 10);
                document.getElementById('minSetting').innerText = rangeMin;
                document.getElementById('maxSetting').innerText = rangeMax;
            } else {
                document.getElementById('distanceContainer').style.display = 'inline-block';
                document.getElementById('minContainer').style.display = 'none';
                document.getElementById('maxContainer').style.display = 'none';

                mindistance = parseInt(document.getElementById('distanceValue').value, 10);
                document.getElementById('distanceSetting').innerText = mindistance;
            }

            posX = parseFloat(document.getElementById('posXValue').value);
            posY = parseFloat(document.getElementById('posYValue').value);
            zoom = parseFloat(document.getElementById('zoomValue').value);

            document.querySelector('#canvas').style.transform = 'translateX(' + posX + '%) translateY(' + posY + '%) scale(' + zoom + ')';

            document.getElementById('posX').innerText = posX + '%';
            document.getElementById('posY').innerText = posY + '%';
            document.getElementById('zoom').innerText = zoom + 'X';

            saveSettings();
            drawCanvas();
        }

        function saveSettings() {
            let saveObj = {
                avg: avg,
                adaptiveRange: adaptiveRange,
                currentPalette: palettes.indexOf(currentPalette),
                opacity: opacity,
                rangeMin: rangeMin,
                rangeMax: rangeMax,
                mindistance: mindistance,
                posX: posX,
                posY: posY,
                zoom: zoom
            };
            localStorage.setItem('settings', JSON.stringify(saveObj));
        }

        function loadSettings() {
            let settings = localStorage.getItem('settings');
            if (settings != null) {
                settings = JSON.parse(settings);
                if(settings.avg){
                    document.getElementById('avgValue').checked = settings.avg;
                }
                if(settings.adaptiveRange){
                    document.getElementById('adaptiveValue').checked = settings.adaptiveRange;
                }

                if (settings.currentPalette && palettes.length > settings.currentPalette) {
                    currentPalette = palettes[settings.currentPalette];
                    document.getElementById('paletteValue').value = settings.currentPalette;
                }

                if (settings.palettes && palettes.length > settings.currentPalette) {
                    currentPalette = palettes[settings.currentPalette];
                    document.getElementById('paletteValue').value = settings.currentPalette;
                }

                if(settings.opacity){
                    document.getElementById('opacityValue').value = settings.opacity;
                }
                if(settings.rangeMin){
                    document.getElementById('minValue').value = settings.rangeMin;
                }
                if(settings.rangeMax){
                    document.getElementById('maxValue').value = settings.rangeMax;
                }
                if(settings.mindistance){
                    document.getElementById('distanceValue').value = settings.mindistance;
                }
                if(settings.posX){
                    document.getElementById('posXValue').value = settings.posX;
                }
                if(settings.posY){
                    document.getElementById('posYValue').value = settings.posY;
                }
                if(settings.zoom){
                    document.getElementById('zoomValue').value = settings.zoom;
                }
            }
        }

        loadSettings();
        updateSettings();
        drawCanvas();

        function map(value, in_min, in_max, out_min, out_max) {
            return (value - in_min) * (out_max - out_min) / (in_max - in_min) +
                out_min;
        }

        function getPaletteColor(val) {
            if (val <= 0) {
                return new Color(currentPalette.stops[0]);
            }
            if (val >= 100) {
                return new Color(currentPalette.stops[currentPalette.stops.length - 1]);
            }
            const stopsCount = currentPalette.stops.length - 1;
            const relevantStop = Math.floor(val / (100 / stopsCount));
            const left = new Color(currentPalette.stops[relevantStop]);
            const right = new Color(currentPalette.stops[relevantStop + 1]);
            const percentage = map(val, relevantStop * (100 / stopsCount), (relevantStop + 1) * (100 / stopsCount), 0, 100);
            return LinearColorInterpolator.findColorBetween(left, right, percentage);
        }

        function setMeter(event) {
            metercoords = {
                x: Math.round(map(event.x, 0, canvas.clientWidth, 0, sizeX)),
                y: Math.round(map(event.y, 0, canvas.clientHeight, 0, sizeY))
            };
            document.getElementById('marker').style.top = metercoords.y * (canvas.clientHeight / sizeY) - 15 + 'px';
            document.getElementById('marker').style.left = metercoords.x * (canvas.clientWidth / sizeX) - 15 + 'px';
            document.getElementById('marker').style.opacity = 1;
        }

        function drawRangeTable(min, max) {
            let valueTable = '';
            for (let i = 0; i < currentPalette.stops.length; i++) {
                var value = 0;
                value = Math.round((min + (((max - min) / currentPalette.stops.length) * i)) * 10) / 10;
                valueTable += '<td style="width:' + 100 / currentPalette.stops.length + '%">' + value;
                if (i == currentPalette.stops.length - 1) {
                    value = Math.round((min + (((max - min) / currentPalette.stops.length) * (i + 1))) * 10) / 10;
                    valueTable += '<span style="float:right">' + value + '</span>';
                }
                valueTable += "</td>";
            }
            document.getElementById('valueTable').innerHTML = valueTable;
        }

        function writeFPS() {
            document.getElementById('fps').innerText = frameCount + "FPS";
            frameCount = 0;
        }

        setInterval(writeFPS, 1000);

        function captureTherm() {
            domtoimage.toJpeg(document.getElementById('image'), {
                    quality: 0.95
                })
                .then(function(dataUrl) {
                    var link = document.createElement('a');
                    link.download = 'thermal.jpg';
                    link.href = dataUrl;
                    link.click();
                });
        }

        function togglePosition() {
            document.querySelectorAll('.position').forEach((elem) => {
                if (elem.classList.contains('hide')) {
                    elem.classList.remove('hide');
                } else {
                    elem.classList.add('hide');
                }
            })
        }
    </script>
</body>

</html>)rawliteral";