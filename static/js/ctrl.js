// console.log("Start")
// Create constants
const gamepadDisplay = document.getElementById('controller-name')
const leftAnalog = document.getElementById('left-analog')
const rightAnalog = document.getElementById('right-analog')
const armUp = document.getElementById('arm-up')
const armDown = document.getElementById('arm-down')
const fireTrigger1 = document.getElementById('fire-trigger1')
const fireTrigger2 = document.getElementById('fire-trigger2')

// Define current target psi variable
currentTargetPsi = 0 

// The -100:100 analog signal is not inherently compatible with the Arduino Signal (that was planned). So this function makes it a two digit signal and limits it from 00:99   
function getAnalog(anaNum) {
    if (anaNum == 0){
    return "00";
    } else if(anaNum==100){
        return "99"
    } else if (anaNum.length == 1){
        return "0"+ anaNum
    } else {
        return anaNum
    }

}

function formatPSI(psiValue){
    if (psiValue == 0){
        return "000";
    } else if (psiValue > 0 && psiValue < 10) {
        return "00" + psiValue
    } else if (psiValue >= 10 && psiValue < 100) {
        return "0" + psiValue
    } else if (psiValue >= 100 ) {
        return psiValue
    } 
} 

// The gamepad API returns true or false. So this function will return a "1" or "0" for the planned final Signal 
function getDigital(dSignal){

    if (dSignal == true){
        return "1";
    } else {
        return "0"
    }
}

// Init socketio client
socket = io();

// Connect to where its Serving
socket.connect('http://127.0.0.1:5000');

// A sort of hand shake to tell the server to send Data 
socket.on('connect',function(){
    socket.send('ctrl');
    document.getElementById("iostatus").innerHTML =  "WSIO Status: Connected";
})

socket.on('disconnect',function(){
    document.getElementById("iostatus").innerHTML =  "WSIO Status: Failed";
    socket.send("150500000");
})


// Receiving data and asking for data back, will also serve as the controller feedback and accumulation  
socket.on('message',function(msg){
    // console.log("Step 3 receive Array data via WS")
    controllerCode = "00000000000"
    if (msg.length != 0 ){
        document.getElementById("potVoltage").innerHTML =  msg[0]
        document.getElementById("xTilt").innerHTML =  msg[1]
        document.getElementById("yTilt").innerHTML =  msg[2]
        document.getElementById("zTilt").innerHTML =  msg[3]
        document.getElementById("tankPSI").innerHTML =  msg[4]
        document.getElementById("compressorTempature").innerHTML =  msg[5]
        
        // console.log("Step 4: Finished changing HTML Data")
    } else if (msg = "Could not find a valid MPU6050 sensor"){
        alert("MPU6050 Sensor (IMU) isn't Responding.\n Check wiring.")
    } else {
        alert("Unexpected Arduino Signal... System my need to be reset. \nProceed With Caution.")
    }

    // Start the gamepadAPI 
    window.addEventListener('gamepadconnected',event => {
        document.getElementById("ctrlstatus").innerHTML =  "Controller Status: Connected";
    })
    
    window.addEventListener('gamepaddisconnected', event =>{
        document.getElementById("ctrlstatus").innerHTML =  "Controller Status: Signal Lost";
    })
    
    // Create gamepad JSON variable to index from
    const gamepads = navigator.getGamepads()
    if (gamepads[0]){

            const standardGamepad = {
                id: gamepads[0].id,
                Laxes: gamepads[0].axes[1].toFixed(2),
                Raxes: gamepads[0].axes[3].toFixed(2),
                ArmUp: gamepads[0].buttons[5].pressed,
                ArmDown: gamepads[0].buttons[4].pressed,
                FireOne: gamepads[0].buttons[3].pressed,
                FireTwo: gamepads[0].buttons[12].pressed,
                IncreasePSI: gamepads[0].buttons[9].pressed,
                DecreasePSI: gamepads[0].buttons[8].pressed
            } 
    
            // Gamepad print outs 
            //  Gamepad Name
            gamepadDisplay.textContent = JSON.parse(JSON.stringify(standardGamepad.id, null,2))
    
            // Analog Signals
            leftAnalogConvert = getAnalog(((parseInt(JSON.parse(JSON.stringify(standardGamepad.Laxes,null,2))*-50)+50)).toFixed(0))
            rightAnalogConvert = getAnalog(((parseInt(JSON.parse(JSON.stringify(standardGamepad.Raxes,null,2))*-50)+50)).toFixed(0))
            
            leftAnalog.textContent = leftAnalogConvert
            rightAnalog.textContent = rightAnalogConvert
            
            // Button Signals
            armUpPh = getDigital(JSON.parse(JSON.stringify(standardGamepad.ArmUp,null,2)))
            armDownPh =getDigital(JSON.parse(JSON.stringify(standardGamepad.ArmDown,null,2)))
            fireOnePh =getDigital(JSON.parse(JSON.stringify(standardGamepad.FireOne,null,2)))
            fireTwoPh =getDigital(JSON.parse(JSON.stringify(standardGamepad.FireTwo,null,2)))
            increase = getDigital(JSON.parse(JSON.stringify(standardGamepad.IncreasePSI,null,2)))
            decrease = getDigital(JSON.parse(JSON.stringify(standardGamepad.DecreasePSI,null,2)))
            
        
            armUp.textContent = armUpPh
            armDown.textContent = armDownPh
            fireTrigger1.textContent = fireOnePh
            fireTrigger2.textContent = fireTwoPh

            // Check to fire
            if (fireOnePh == "1" && fireTwoPh == "1"){
                userReadyToFire = "1"
            } else {
                userReadyToFire = "0"
            }

            //  We don't want the arm actuation being told to move up and down at the same time. So this prohibits that from happening.
            if ( armUpPh == "1" && armDownPh == "1"){
                armDownPh = "0"
                armUpPh = "0"
                document.getElementById("arm-up").innerHTML = "Act. Safety Condition Triggered!"
                document.getElementById("arm-down").innerHTML = "Resulting to 0!"
            }

            // To increase and decrease the target PSI
            if(increase == "1"){
                currentTargetPsi++
            } else if (decrease == "1"){
                currentTargetPsi--
            } else if (currentTargetPsi < 0){
                currentTargetPsi = 0
            } else if (currentTargetPsi >= 110){
                currentTargetPsi = 110
            }

    document.getElementById("target-psi").innerHTML = formatPSI(currentTargetPsi)

    // controllerCode to send to serial
    controllerCode = "1"+ leftAnalogConvert + rightAnalogConvert + armUpPh + armDownPh + userReadyToFire + formatPSI(currentTargetPsi)
    // console.log("Step 5 Assemble controller code")
    console.log(controllerCode)


    // Send out to Receive more
    socket.send(controllerCode);
    // console.log("Step 6: Send controller code back over WS")
}

})

// console.log("finished")