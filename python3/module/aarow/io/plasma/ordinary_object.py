import pyarrow as pa
import pyarrow.plasma as plasma
import numpy as np


def random_object_id():
    return plasma.ObjectID(np.random.bytes(20))


def high_level_save_get_api(client):
    # save & get single data
    object_id = client.put("hello, world")
    print(client.get(object_id))

    # save & get multi data
    object_id1 = client.put(1)
    object_id2 = client.put(2)
    print(client.get([object_id1, object_id2]))


def low_level_save_get_api(client):
    # Create an object buffer.
    object_id = plasma.ObjectID(20 * b"a")
    object_size = 1000
    buffer = memoryview(client.create(object_id, object_size))

    # Write to the buffer.
    for i in range(1000):
        buffer[i] = i % 128

    # Seal the object. This makes the object immutable and available to other clients.
    client.seal(object_id)

    # Create a different client
    client2 = plasma.connect("/tmp/plasma")

    # Get the object in the second client. This blocks until the object has been sealed.
    object_id2 = plasma.ObjectID(20 * b"a")
    [buffer2] = client2.get_buffers([object_id2], timeout_ms=5)
    view2 = memoryview(buffer2)
    print(buffer, buffer2)
    print(bytes(buffer[1:4]), bytes(view2[1:4]))


if __name__ == '__main__':
    client_ = plasma.connect("/tmp/plasma")
    plasma_id = random_object_id()
    print(plasma_id)

    high_level_save_get_api(client_)
    low_level_save_get_api(client_)
