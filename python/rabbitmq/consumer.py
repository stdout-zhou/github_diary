import pika

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

channel.queue_declare(queue=RabbitMQConfig["queue_name"], durable=False)


def callback(ch, method, properties, body):
    ch.basic_ack(delivery_tag=method.delivery_tag)
    print("message is {}".format(body.decode()))


channel.basic_consume(RabbitMQConfig["queue_name"], callback)

channel.start_consuming()