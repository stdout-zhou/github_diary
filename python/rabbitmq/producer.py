import pika
import json

RabbitMQConfig = {
    "account": "admin",
    "password": "admin",
    "host": "127.0.0.1",
    "port": 5672,
    "queue_name": "std_mq",
}

credentials = pika.PlainCredentials(RabbitMQConfig["account"], RabbitMQConfig["password"])

connection = pika.BlockingConnection(pika.ConnectionParameters(host=RabbitMQConfig["host"],
                                                               port=RabbitMQConfig["port"],
                                                               credentials=credentials))
channel = connection.channel()

result = channel.queue_declare(queue=RabbitMQConfig["queue_name"])

for i in range(10):
    message = json.dumps({'OrderId': "1000%s" % i})
    channel.basic_publish(exchange='',
                          routing_key=RabbitMQConfig["queue_name"],
                          body=message)
    print(message)

connection.close()