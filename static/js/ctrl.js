// Create constants
const gamepadDisplay = document.getElementById('controller-name')
const leftAnalog = document.getElementById('left-analog')
const rightAnalog = document.getElementById('right-analog')
const armUp = document.getElementById('arm-up')
const armDown = document.getElementById('arm-down')
const fireTrigger1 = document.getElementById('fire-trigger1')
const fireTrigger2 = document.getElementById('fire-trigger2')



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
    document.getElementById("status").innerHTML =  "WSIO Status: Failed";
})


// Receiving data and asking for data back, will also serve as the controller feedback and accumulation  
socket.on('message',function(msg){
    // console.log("Step 3 receive Array data via WS")
    controllerCode = "000000000"
    if (msg.length != 0 ){
        document.getElementById("potVoltage").innerHTML =  msg[0]
        document.getElementById("xTilt").innerHTML =  msg[1]
        document.getElementById("yTilt").innerHTML =  msg[2]
        document.getElementById("zTilt").innerHTML =  msg[3]
        // console.log("Step 4: Finish changing HTML Data")
    } else {
        // console.log("no can do buckaroo")
    }
    // Receiving and displaying
    


    // console.log("called")

    window.addEventListener('gamepadconnected',event => {
        // console.log("Game Controller Detected")
        document.getElementById("ctrlstatus").innerHTML =  "Controller Status: Connected";
        // console.log(event.gamepad)
    })
    
    window.addEventListener('gamepaddisconnected', event =>{
        // console.log("Game Controller Detected")
        document.getElementById("ctrlstatus").innerHTML =  "Controller Status: Signal Lost";
        // console.log(event.gamepad)
    })
    
    const gamepads = navigator.getGamepads()
    if (gamepads[0]){
        const gamepadState = {
            id: gamepads[0].id,
            Laxes: gamepads[0].axes[1].toFixed(2),
            Raxes: gamepads[0].axes[3].toFixed(2),
            ArmUp: gamepads[0].buttons[5].pressed,
            ArmDown: gamepads[0].buttons[4].pressed,
            FireOne: gamepads[0].buttons[3].pressed,
            FireTwo: gamepads[0].buttons[12].pressed
        }
        // Print gamepad in general
        // console.log(gamepadState)

        //  Gamepad Name
        gamepadDisplay.textContent = JSON.parse(JSON.stringify(gamepadState.id, null,2))

        // Analog Signals
        leftAnalogConvert = getAnalog(((parseInt(JSON.parse(JSON.stringify(gamepadState.Laxes,null,2))*-50)+50)).toFixed(0))
        rightAnalogConvert = getAnalog(((parseInt(JSON.parse(JSON.stringify(gamepadState.Raxes,null,2))*-50)+50)).toFixed(0))
        
        leftAnalog.textContent = leftAnalogConvert
        rightAnalog.textContent = rightAnalogConvert
        
        // Button Signals
        armUpPh = getDigital(JSON.parse(JSON.stringify(gamepadState.ArmUp,null,2)))
        armDownPh =getDigital(JSON.parse(JSON.stringify(gamepadState.ArmDown,null,2)))
        fireOnePh =getDigital(JSON.parse(JSON.stringify(gamepadState.FireOne,null,2)))
        fireTwoPh =getDigital(JSON.parse(JSON.stringify(gamepadState.FireTwo,null,2)))
    
        armUp.textContent = armUpPh
        armDown.textContent = armDownPh
        fireTrigger1.textContent = fireOnePh
        fireTrigger2.textContent =fireTwoPh

        if ( armUpPh == "1" && armDownPh == "1"){
            armDownPh = "0"
            armUpPh = "0"
            document.getElementById("arm-up").innerHTML = "Act. Safety Condition Triggered!"
            document.getElementById("arm-down").innerHTML = "Resulting to 0!"
        }

        // controllerCode to send to serial
        controllerCode = "1"+ leftAnalogConvert + rightAnalogConvert + armUpPh + armDownPh + fireOnePh + fireTwoPh
        // console.log("Step 5 Assemble controller code")
        console.log(controllerCode)
        
    }


    // Send out to Receive more
    socket.send(controllerCode);
    // console.log("Step 6: Send controller code back over WS")
    
})

