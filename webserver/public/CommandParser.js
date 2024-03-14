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
        if (!data.startsWith("#")) return;

        const parts = data.slice(1).split("#");
        const command = parts[0];
        const parameters = parts[1] ? this.parseParameters(parts[1]) : [];

        if (command in this.handlers) {
            this.handlers[command](...parameters);
        } else {
            console.warn(`No handler registered for command: ${command}`);
        }
    }

    parseParameters(paramString) {
        return paramString.split("_");
    }
};

const parser = new CommandParser()

parser.registerCommand("MAP", (mapLength, ...coords) => {
    const mapLengthInt = parseInt(mapLength, 10);
    const map = [];
    for (let i = 0; i < mapLengthInt; i++) {
        const x = parseFloat(coords[i * 2]);
        const y = parseFloat(coords[i * 2 + 1]);
        map.push([x, y]);
    }
    app.graph.map = map
    setup()
});

parser.registerCommand("MST", (mapLength, ...params) => {
    const mapLengthInt = parseInt(mapLength, 10);
    const map = [];
    for (let i = 0; i < mapLengthInt; i++) {
        const a = parseInt(params[i * 3]);
        const b = parseInt(params[i * 3 + 1]);
        const color = params[i * 3 + 2].trim()
        map.push([a, b, color]);
    }
    app.graph.edges = map
    // setup()
});