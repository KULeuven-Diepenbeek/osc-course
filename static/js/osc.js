function toggleAnswer(target) {
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
}  