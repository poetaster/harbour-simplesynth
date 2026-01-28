WorkerScript.onMessage = function(msg) {
    if (msg.action === 'play') {
        msg.synth.play();
    }
    if (msg.action === 'setDuration') {
        msg.synth.setDuration(msg.duration);
    }
    if (msg.action === 'setDuration') {
        msg.synth.setDuration(msg.duration);
    }
}
