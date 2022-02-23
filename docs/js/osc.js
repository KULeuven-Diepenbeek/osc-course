function toggleAnswer(target, combo) {
  var text = combo%2;
  combo = Math.floor( combo / 2 ); 
  var image = combo%2

  if(target ==='q711') {
    x = document.getElementById('q711')
    if (x.style.visibility === "hidden") {
      x.style.visibility = "visible";
    } else {
      x.style.visibility = "hidden";
    }
  }

  if(target ==='q712') {
    x = document.getElementById('q712')
    if (x.style.visibility === "hidden") {
      x.style.visibility = "visible";
    } else {
      x.style.visibility = "hidden";
    }
  }

  if(target ==='q713') {
    x = document.getElementById('q713')
    if (x.src.includes('img/sched/ss_preemt_priority_answer.png')) {
      x.src = '../../img/sched/ss_preemt_priority.png'
    } else {
      x.src = '../../img/sched/ss_preemt_priority_answer.png'
    }
    // document.getElementById('q713').src='../../img/sched/ss_preemt_priority_answer.png'
  }

  if(target ==='q714') {
    x = document.getElementById('q714')
    if (x.style.visibility === "hidden") {
      x.style.visibility = "visible";
    } else {
      x.style.visibility = "hidden";
    }
  }

  if(target ==='q721') {
    x = document.getElementById('div_q721')
    if (x.style.visibility === "hidden") {
      x.style.visibility = "visible";
    } else {
      x.style.visibility = "hidden";
    }
    x = document.getElementById('img_q721')
    if (x.src.includes('img/sched/ss_ts.png')) {
      x.src = '../../img/sched/ss_ts10ms.png'
    } else {
      x.src = '../../img/sched/ss_ts.png'
    }
  }

  if(target ==='q722') {
    x = document.getElementById('div_q722')
    if (x.style.visibility === "hidden") {
      x.style.visibility = "visible";
    } else {
      x.style.visibility = "hidden";
    }
    x = document.getElementById('img_q722')
    if (x.src.includes('img/sched/ss_ts_l.png')) {
      x.src = '../../img/sched/ss_ts100ms.png'
    } else {
      x.src = '../../img/sched/ss_ts_l.png'
    }
  }

    if(text === 1) {
      x = document.getElementById('div_'+target)
      if (x.style.visibility === "hidden") {
        x.style.visibility = "visible";
      } else {
        x.style.visibility = "hidden";
      }
    }
    if(image === 1) {
      x = document.getElementById('img_q811')
      if (x.src.includes('img/sched/ss_ts_l.png')) {
        x.src = '../../img/sched/ss_ts100ms.png'
      } else {
        x.src = '../../img/sched/ss_ts_l.png'
      }
    }


}  

function toggleDisplay(targetID) {
  x = document.getElementById(targetID);

  // TODO: refactor to add/remove classname hidden, will be much much smoother!
  if (x.style.display !== "block" && x.style.display !== "grid") {
    if( x.className.includes("multicol") ) {
      x.style.display = "grid";
    }
    else {
      x.style.display = "block";
    }
  } else {
    x.style.display = "none";
  }
}