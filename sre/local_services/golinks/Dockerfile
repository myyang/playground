FROM golang:alpine

EXPOSE 8067

RUN go install -v github.com/myyang/go/cmd/go@latest

CMD ./bin/go --data /var/data
