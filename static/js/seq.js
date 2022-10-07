sequence = []

var textbox = document.getElementById("seqCode");
textbox.addEventListener("keypress", function(event) {
  if (event.key === "Enter") {
    event.preventDefault();
    document.getElementById("pcButton").click();
  }
})

function checkMovement(input){
    console.log(input)

    if (input == "moveforward"){
        return  1

    } else if (input == "movebackward"){
        return 2

    } else if (input == "turnleft") {
        return 3

    } else if (input == "turnright") {
        return 4

    } else if (input == "armup"){
        return 5

    } else if (input == "armdown"){
        return 6

    } else if (input == "pressureto"){
        return 7

    } else {
        alert("invalid movement")
        return "F"

    }
}

function checkIdx(input){
    if (input > 9 || isNaN(Number(input))){
        alert("invalid index")
        return "F"
    } else {
        return input
    }
}

function checkTime(input){
    if (isNaN(Number(input))){
        alert("Invalid Time \nRemember: You should not use terminating symbols.")
        return "F"
    } else {
        return input
    }
}

function checkHtml(input){
   if (input == undefined){
    return ["---","---","---"]
   } else {
    
    return input
   }

} 

function sequenceToHtml(input){
    input = input
    
    // Index 0
    idx0 = checkHtml(input[0])
    document.getElementById("step-1").innerHTML = idx0[0]
    document.getElementById("stepT-1").innerHTML = idx0[2]

    // Index 1
    idx1 = checkHtml(input[1])
    document.getElementById("step-2").innerHTML = idx1[0]
    document.getElementById("stepT-2").innerHTML = idx1[2]

    // Index 2
    idx2 = checkHtml(input[2])
    document.getElementById("step-3").innerHTML = idx2[0]
    document.getElementById("stepT-3").innerHTML = idx2[2]

    // Index 3
    idx3 = checkHtml(input[3])
    document.getElementById("step-4").innerHTML = idx3[0]
    document.getElementById("stepT-4").innerHTML = idx3[2]

    // Index 4
    idx4 = checkHtml(input[4])
    document.getElementById("step-5").innerHTML = idx4[0]
    document.getElementById("stepT-5").innerHTML = idx4[2]

    // Index 5
    idx5 = checkHtml(input[5])
    document.getElementById("step-6").innerHTML = idx5[0]
    document.getElementById("stepT-6").innerHTML = idx5[2]

    // Index 6
    idx6 = checkHtml(input[6])
    document.getElementById("step-7").innerHTML = idx6[0]
    document.getElementById("stepT-7").innerHTML = idx6[2]

    // Index 7
    idx7 = checkHtml(input[7])
    document.getElementById("step-8").innerHTML = idx7[0]
    document.getElementById("stepT-8").innerHTML = idx7[2]

    // Index 8
    idx8 = checkHtml(input[8])
    document.getElementById("step-9").innerHTML = idx8[0]
    document.getElementById("stepT-9").innerHTML = idx8[2]

    // Index 9
    idx9 = checkHtml(input[9])
    document.getElementById("step-10").innerHTML = idx9[0]
    document.getElementById("stepT-10").innerHTML = idx9[2]
}

function processCode() {
    // Take in input
    var input = document.getElementById("seqCode").value;
 
    // create code to analyze 
    if (input.includes("(") && input.includes(",") && input.includes(")")){
    
        cleanOpenPara = input.split("(")
        // console.log(cleanOpenPara)
        cleanComma = cleanOpenPara[1].split(",")
        // console.log(cleanComma)
        cleanClosePara = cleanComma[1].replace(")","")
        // console.log(cleanClosePara)
    
        movement = checkMovement(cleanOpenPara[0].toLowerCase())
        idx = checkIdx(cleanComma[0])
        time = checkTime(cleanClosePara) 

        // Create final output
        // idx0: Movement, idx1: index,

        if ( movement == "F" || idx == "F" || time == "F"){
            alert("Errors detected! Code not sequenced")
        } else {
            seqStep = [movement, idx, time]
            sequence[seqStep[1]] = seqStep
            console.log(sequence)
            sequenceToHtml(sequence)
        }


    } else {
        alert("Input could not be determined...")
        console.log("Invalid Input")
    }
}

function sendSeq(){
    // Fill in input blanks
    console.log("signal")
    console.log(sequence)

    // Separate times and movements 
    times = [] 
    moves = []

    // index through times and movements and send out serial and wait commands accordingly \

    // clean sequence
    
    sequence = []
    sequenceToHtml(sequence)
}
