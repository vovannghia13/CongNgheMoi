from flask_socketio import SocketIO, emit
from flask import Flask, render_template, url_for, copy_current_request_context
from random import random
from time import sleep
from threading import Thread, Event

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
app.config['DEBUG'] = True

# turn the flask app into a socketio app
socketio = SocketIO(app, async_mode=None, logger=True, engineio_logger=True)

# random number Generator Thread
thread = Thread()
thread_stop_event = Event()


def randomNumberGenerator():
    print("Making random numbers")
    while not thread_stop_event.isSet():
        number = round(random()*10, 3)
        print(number)
        socketio.emit('newnumber', {'number': number}, namespace='/temperature')
        socketio.sleep(2)


@app.route("/")
def home():
    return render_template('index.html')


@app.route("/demo")
def demo():
    return render_template('demo.html')


@socketio.on('connect', namespace='/temperature')
def client_connect():
    # need visibility of the global thread object
    global thread
    print('Client connected')

    # Start the random number generator thread only if the thread has not been started before.
    if not thread.isAlive():
        print("Starting Thread")
        thread = socketio.start_background_task(randomNumberGenerator)


@socketio.on('disconnect', namespace='/temperature')
def client_disconnect():
    print('Client disconnected')


if __name__ == "__main__":
    app.run(debug=True)
