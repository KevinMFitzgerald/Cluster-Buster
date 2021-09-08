String homePage = F(R"=====(//F() macro stores the data in flash memory rather than SRAM
<!DOCTYPE html>
<html>
  <head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
    <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  </head>
 <style>
* {box-sizing: border-box;}
ul {list-style-type: none;}
body {font-family: Verdana, sans-serif;}

.month {
  padding: 70px 25px;
  width: 100%;
  background: #1abc9c;
  text-align: center;
}
.month ul {
  margin: 0;
  padding: 0;
}

.month ul li {
  color: white;
  font-size: 20px;
  text-transform: uppercase;
  letter-spacing: 3px;
}

.month .prev {
  float: left;
  padding-top: 10px;
}

.month .next {
  float: right;
  padding-top: 10px;
}

.weekdays {
  margin: 10;
  padding: 10px 0;
  background-color: #ddd;
}

.weekdays li {
  display: inline-block;
  width: 14.6%;
  color: #666;
  text-align: center;
}

.days {
  padding: 1px 0;
  background: #eee;
  margin: 0;
}

.days li {
  list-style-type: none;
  display: inline-block;
  width: 13.6%;
  text-align: center;
  margin-bottom: 5px;
  font-size:12px;
  color: #777;
}
.days li .active {
  padding: 5px;
  background: #1abc9c;
  color: white !important
}

/* Add media queries for smaller screens */
@media screen and (max-width:720px) {
  .weekdays li, .days li {width: 13.1%;}
}

@media screen and (max-width: 420px) {
  .weekdays li, .days li {width: 12.5%;}
  .days li .active {padding: 2px;}
}

@media screen and (max-width: 290px) {
  .weekdays li, .days li {width: 12.2%;}
}
.mychart {
    width: 75%;
    height: 100%;
    }
   .main-container {
     display: flex;
     flex-direction: column;
     background-color: White;
   }


   .content-div {
     display: flex;
     flex-direction: row;
     background-color: White;
     width: 100%;
     border: 1px solid black;
     }
     .content-div1 {
     display: flex;
     flex-direction: none;
     background-color: White;
     width: 100%;
     border: 1px solid black;
     }
     .display-calander {
        background-color: #f0f0f0;
        width: 45%;
        border: 1px solid black;
        border-radius: 2%;
        margin: 5px;
        
      }
       .display-div {
        display: flex;
        background-color: #f0f0f0;
        width: 40%;
        border: 1px solid black;
        border-radius: 2%;
        text-align: center;
        font-weight: bold;
        margin: 5px;
        justify-content: center;
      align-items: center;
      }
          .para {
        font-size: 30px;
        font-weight: bold;
        text-align: center;
        margin: 10px;
      }
      .date-time-para {
        font-size: 18px;
        font-weight: normal;
        text-align: center;
        margin: 10px;
      }
       .button { 
         padding:10px 10px 10px 10px;
         width:100%;
         background-color: #50FF50;
         font-size: 100%;
       }
       
 </style>
  <body>
  <div class="main-container">
        <div class="content-div">
          <div class="display-div"style="width:40 %;">
              <p class="date-time-para">Date:<span id="Date"></span> </p>
              <p class="date-time-para">Time:<span id="Time"></span> </p>
          </div>
          <div class="display-div" style="width: 60%;">
              <p class="para">Cluster Buster</p>
          </div>
    </div>
        <div class="content-div1">
          <div class="display-calander" style="width: 43%;">
    <div class="month">      
    <ul>
    <li>
      <span id="Month">"Failed to date"</span><br>
      <span style="font-size:18px">2021</span>
    </li>
  </ul>
</div>

<ul class="weekdays" >
  <li>Mo</li>
  <li>Tu</li>
  <li>We</li>
  <li>Th</li>
  <li>Fr</li>
  <li>Sa</li>
  <li>Su</li>
</ul>

<ul class="days" >  
  <li>1</li>
  <li>2</li>
  <li>3</li>
  <li>4</li>
  <li>5</li>
  <li>6</li>
  <li>7</li>
  <li>8</li>
  <li>9</li>
  <li><span class="active">10</span></li>
  <li>11</li>
  <li>12</li>
  <li>13</li>
  <li>14</li>
  <li>15</li>
  <li>16</li>
  <li>17</li>
  <li>18</li>
  <li>19</li>
  <li>20</li>
  <li>21</li>
  <li>22</li>
  <li>23</li>
  <li>24</li>
  <li>25</li>
  <li>26</li>
  <li>27</li>
  <li>28</li>
  <li>29</li>
  <li>30</li>
  <li>31</li>
</ul>
 </div>
      <div class="display-div" style="width: 32.5%; margin-right: 0px;">
              <h1>DHT11 value :<span id="DHT11">0</span></h1><br>
          </div>
          <div class="display-div" style="width: 32.5%; margin-left: 0px;">
              Barametric pressure: <br>
              <span id="Pressure">0</span></h1><br>
          </div>
        </div>
        <div class="content-div">
          <div class="display-div" style="flex-direction: column""width: 70%;">
            <div class="display-div" style="width: 95%;">
             which side of the head is the pain
            </div>
             <div class="display-div" style="width: 95%;">
             <img src = "https://prod-images-static.radiopaedia.org/images/18717/7b8b0fc3cc9ac6c359320f24b9644d_gallery.jpeg"width="90%">
             </div>
             <div class="display-div" style="width: 95%;">
               <input type="checkbox" onmousedown=location.href="/L" onmouseup=location.href="/"">
          <label for="Left"> Left side</label>
                 <input type="checkbox" onmousedown=location.href="/R" onmouseup=location.href="/">
          <label for="Right"> Right side</label><br> 
            </div>
          </div>
    <div class="mychart" >
      <canvas id="myChart"></canvas>
    </div>

    <script>
      let labels = [
        '0 secs',
        '0 secs',
        '0 secs',
        '0 secs',
        '0 secs',
        '0 secs',
        '0 secs',
        '0 secs',
        '0 secs',
        '0 secs'
      ];//sets all x axis to 0;
      let data = {
        labels: labels,
        datasets: [{
          label: 'Heart Rate',
          backgroundColor: 'rgb(255, 99, 132)',
          borderColor: 'rgb(255, 99, 132)',
          data: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]//y axis 
        }]
      };

      let config = {
        type: 'line',
        data,
        options: {}
      };

      var myChart = new Chart(
        document.getElementById('myChart'),
        config
      );
     
     
      function HeartRateTimerFunction() {
        var xhttp = new XMLHttpRequest();//ajax
        xhttp.onreadystatechange = function() {//onreadystatechange defines a function to be executed when the readyState changes.
        if (this.readyState == 4 && this.status == 200) {//4: request finished and response is ready, 200: means the http request is "OK"
        var x = ((new Date()).getTime()/1000)%100;//disolays time on the x axise, once the time is above 100 seconds it resets to 0
        var y= this.responseText;//passes the heart rate vaules to the y axis
        config.data.labels.shift();// moves the first element of the data.lables
        config.data.labels.push(x.toFixed(0) + " secs");//
        config.data.datasets[0].data.shift();// moves the first element in the datasets array which is the Y axis 
        config.data.datasets[0].data.push(y);// adds the vaule of the heart rate on Y axis 
        myChart.update();//updates the chart with the new points
    }
  };
  xhttp.open("GET", "getData", true);
  xhttp.send();
      }
       function TempTimerFunction() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
         document.getElementById("DHT11").innerHTML =//looks for a span id inside my html page.
      this.responseText;//updates the span id in the html page
        }
  };
  xhttp.open("GET", "temp", true);
  xhttp.send();
      }
        function PressureTimerFunction() {
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
        document.getElementById("Pressure").innerHTML =
      this.responseText;
        }
  };
  xhttp.open("GET", "sendPressure", true);
  xhttp.send();
      }
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
        document.getElementById("Month").innerHTML =
      this.responseText;
        }
  };
  xhttp.open("GET", "Month", true);
  xhttp.send();

      var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
        document.getElementById("Date").innerHTML =
      this.responseText;
        }
  };
  xhttp.open("GET", "Date", true);
  xhttp.send();
  
        function TimerFunction(){
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
        document.getElementById("Time").innerHTML =
      this.responseText;
        }
  };
  xhttp.open("GET", "Time", true);
  xhttp.send();
     }
      
      setInterval(HeartRateTimerFunction, 10000);//timers set to run the functions at the given time in mills
      setInterval(TempTimerFunction, 1000);
      setInterval(PressureTimerFunction, 1000);
      setInterval(TimerFunction,1000);
    </script>
  </body>
</html>
)=====");
