from .api import app

if __name__ == "__main__":
    # Code isn't thread safe, since we are using matplotlib.pyplot
    # to draw images.
    app.run(host='0.0.0.0', port=5050, debug=False, threaded=False, processes=2)
