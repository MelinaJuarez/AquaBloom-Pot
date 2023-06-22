const char PAGE_MAIN[] PROGMEM = R"=====(
  <!DOCTYPE html>
  <html lang="en" class="js-focus-visible">
  <title>AquaBloom Pot</title>
    <style>
      table {
        position: relative;
        width:100%;
        border-spacing: 0px;
      }
      tr {
        border: 1px solid white;
        font-family: "Verdana", "Arial", sans-serif;
        font-size: 20px;
      }
      th {
        height: 20px;
        padding: 3px 15px;
        background-color: #343a40;
        color: #FFFFFF !important;
        }
      td {
        height: 20px;
         padding: 3px 15px;
      }
      .tabledata {
        font-size: 24px;
        position: relative;
        padding-left: 5px;
        padding-top: 5px;
        height:   25px;
        border-radius: 5px;
        color: #FFFFFF;
        line-height: 20px;
        transition: all 200ms ease-in-out;
        background-color: #00AA00;
      }
      .chslider {
        width: 30%;
        height: 55px;
        outline: none;
        height: 25px;
      }
      .bodytext {
        font-family: "Verdana", "Arial", sans-serif;
        font-size: 24px;
        text-align: left;
        font-weight: light;
        border-radius: 5px;
        display:inline;
      }
      .navbar {
        width: 100%;
        height: 50px;
        margin: 0;
        padding: 10px 0px;
        background-color: #FFF;
        color: #000000;
        border-bottom: 5px solid #293578;
      }
      .fixed-top {
        position: fixed;
        top: 0;
        right: 0;
        left: 0;
        z-index: 1030;
      }
      .navtitle {
        float: left;
        height: 50px;
        font-family: "Verdana", "Arial", sans-serif;
        font-size: 50px;
        font-weight: bold;
        line-height: 50px;
        padding-left: 20px;
      }
     .navheading {
       position: fixed;
       left: 60%;
       height: 50px;
       font-family: "Verdana", "Arial", sans-serif;
       font-size: 20px;
       font-weight: bold;
       line-height: 20px;
       padding-right: 20px;
     }
     .navdata {
        justify-content: flex-end;
        position: fixed;
        left: 70%;
        height: 50px;
        font-family: "Verdana", "Arial", sans-serif;
        font-size: 20px;
        font-weight: bold;
        line-height: 20px;
        padding-right: 20px;
     }
      .category {
        font-family: "Verdana", "Arial", sans-serif;
        font-weight: bold;
        font-size: 32px;
        line-height: 50px;
        padding: 20px 10px 0px 10px;
        color: #000000;
      }
      .heading {
        font-family: "Verdana", "Arial", sans-serif;
        font-weight: normal;
        font-size: 28px;
        text-align: left;
      }
    
      .btn {
        background-color: #444444;
        border: none;
        color: white;
        padding: 10px 20px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 16px;
        margin: 4px 2px;
        cursor: pointer;
      }
      .foot {
        font-family: "Verdana", "Arial", sans-serif;
        font-size: 20px;
        position: relative;
        height:   30px;
        text-align: center;   
        color: #AAAAAA;
        line-height: 20px;
      }
      .container {
        max-width: 1800px;
        margin: 0 auto;
      }
      table tr:first-child th:first-child {
        border-top-left-radius: 5px;
      }
      table tr:first-child th:last-child {
        border-top-right-radius: 5px;
      }
      table tr:last-child td:first-child {
        border-bottom-left-radius: 5px;
      }
      table tr:last-child td:last-child {
        border-bottom-right-radius: 5px;
      }
      
    </style>
    <body style="background-color: #efefef" onload="process()">
    
      <header>
        <div class="navbar fixed-top">
            <div class="container">
              <div class="navtitle">AquaBloom Pot</div>
              <div class="navdata" id = "date">mm/dd/yyyy</div>
              <div class="navheading">DATE</div><br>
              <div class="navdata" id = "time">00:00:00</div>
              <div class="navheading">TIME</div>
              
            </div>
        </div>
      </header>
    
      <main class="container" style="margin-top:70px">
        <div class="category">Sensor Readings</div>
        <div style="border-radius: 10px !important;">
        <table style="width:50%">
        <colgroup>
          <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
          <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
          <col span="1" style="background-color:rgb(180,180,180); width: 15%; color:#000000 ;">
        </colgroup>
        <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
        <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
        <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
        <tr>
          <th colspan="1"><div class="heading">Sensor</div></th>
          <th colspan="1"><div class="heading">Value</div></th>
        </tr>
        <tr>
          <td><div class="bodytext">Humidity</div></td>
          <td><div class="tabledata" id = "b0"></div></td>
        </tr>
        <tr>
          <td><div class="bodytext">Temperature</div></td>
          <td><div class="tabledata" id = "b1"></div></td>
        </tr>
          <tr>
          <td><div class="bodytext">Dropper</div></td>
          <td><div class="tabledata" id = "switch"></div></td>
        </tr>
        </table>
      </div>
      <br>
      <div class="bodytext">Critical Humidity (When will the Dropper open: <span id="ch"></span>)</div>
      <br>
      <input type="range" class="chslider" min="0" max="100" value = "0" width = "0%" oninput="UpdateSlider(this.value)"/>
      <br>
      <br>
    </main>
    <footer div class="foot" id = "temp" >Proyecto de Electronica Digital con un ESP32</div></footer>
    
    </body>
    <script type = "text/javascript">
    
      // global variable visible to all java functions
      var xmlHttp=createXmlHttpObject();
      // function to create XML object
      function createXmlHttpObject(){
        if(window.XMLHttpRequest){
          xmlHttp=new XMLHttpRequest();
        }
        else{
          xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
        }
        return xmlHttp;
      }
      function UpdateSlider(value) {
        var xhttp = new XMLHttpRequest();
        // Para obtener los valores de humedad critica
        xhttp.onreadystatechange = function() {
          if (this.readyState == 4 && this.status == 200) {
            document.getElementById("ch").innerHTML=this.responseText;
          }
        }
        xhttp.open("PUT", "UPDATE_SLIDER?VALUE="+value, true);
        xhttp.send();
      }
      // function to handle the response from the ESP
      function response(){
        var message;
        var barwidth;
        var currentsensor;
        var xmlResponse;
        var xmldoc;
        var dt = new Date();
        var color = "#e8e8e8";
       
        // get the xml stream
        xmlResponse=xmlHttp.responseXML;
    
        // get host date and time
        document.getElementById("time").innerHTML = dt.toLocaleTimeString();
        document.getElementById("date").innerHTML = dt.toLocaleDateString();
    
        // A0
        xmldoc = xmlResponse.getElementsByTagName("B0"); //bits for A0
        message = xmldoc[0].firstChild.nodeValue;
        
        color = "#0000aa";
        
        
        barwidth = message / 1;
        message = xmldoc[0].firstChild.nodeValue;
        document.getElementById("b0").innerHTML=message;
        document.getElementById("b0").style.width=(barwidth+"%");
        
        
        
    
        // A1
        xmldoc = xmlResponse.getElementsByTagName("B1");
        message = xmldoc[0].firstChild.nodeValue;
        
        color = "#0000aa";
        
        document.getElementById("b1").innerHTML=message;
        width = message / 1;
        message = xmldoc[0].firstChild.nodeValue;
        document.getElementById("b1").style.width=(width+"%");
        document.getElementById("b1").style.backgroundColor=color;
        //document.getElementById("b1").style.borderRadius="5px";
        
        
           
        xmldoc = xmlResponse.getElementsByTagName("SWITCH");
        message = xmldoc[0].firstChild.nodeValue;
        document.getElementById("switch").style.backgroundColor="rgb(200,200,200)";
        // update the text in the table
        if (message == 0){
          document.getElementById("switch").innerHTML="Closed";
          document.getElementById("switch").style.color="#0000AA"; 
        }
        else {
          document.getElementById("switch").innerHTML="Opened";
          document.getElementById("switch").style.color="#00AA00";
        }
       }
    
        
        
    
      
      function process(){
       
       if(xmlHttp.readyState==0 || xmlHttp.readyState==4) {
          xmlHttp.open("PUT","xml",true);
          xmlHttp.onreadystatechange=response;
          xmlHttp.send(null);
        }       
          // you may have to play with this value, big pages need more porcessing time, and hence
          // a longer timeout
          setTimeout("process()",100);
      }
    
    
    </script>
  </html>
)=====";