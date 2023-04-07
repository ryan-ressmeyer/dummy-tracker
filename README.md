### Dummy Eyetracker

This project spawns a dummy container that uses the same communication protocol as the actual cvdpi eye tracker. Once spawned, the contianer listens on 127.0.0.1:5555 of the host machine for a tcp connection using the request/reply zmq pattern. A simple script to interface with the container is given in connect.py. 

If you don't already have docker installed, use the install_docker.sh script. You then have to build the contianer using the build.sh script. Finally, you can run the demo by running the run.sh script in one terminal, opening a second, then running the connect.py script. You will need to have pyzmq in your python environment (pip install pyzmq).