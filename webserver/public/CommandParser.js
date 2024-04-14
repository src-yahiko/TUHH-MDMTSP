class CommandParser {
    constructor() {
        this.handlers = {};
    }

    registerCommand(command, handler) {
        if (typeof handler !== "function") {
            throw new Error("Handler must be a function");
        }
        this.handlers[command] = handler;
    }

    parse(data) {
        data = data.split('\n');
        data.forEach(line => {

            if (!line.startsWith("#")) {
                if (line.startsWith("Exit code 0")) {
                    console.log(line)
                    setup()
                    draw2()
                }
                return
            };

            const parts = line.slice(1).split("#");
            const command = parts[0];
            const parameters = parts[1] ? this.parseParameters(parts[1]) : [];

            if (command in this.handlers) {
                this.handlers[command](...parameters);
            } else {
                console.warn(`No handler registered for command: ${command}`);
            }
        })
    }

    parseParameters(paramString) {
        return paramString.split("_");
    }
};

const parser = new CommandParser()

parser.registerCommand("RESET", () => {
    app.graph.map = {}
    app.graph.edges = []
    vertices = []
});

parser.registerCommand("POINT", (nodeId, ...coords) => {
    app.graph.map[nodeId] = [...coords, false]
});

parser.registerCommand("DEPOT", (nodeId) => {
    app.graph.map[nodeId][2] = true
});

parser.registerCommand("EDGE", (...fromToWeight) => {
    app.graph.edges.push(fromToWeight)
});