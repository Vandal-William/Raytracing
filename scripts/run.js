const { spawnSync } = require("child_process");

const commands = {
  "build:release": "make build-release",
  "build:debug": "make build-debug",
  "start": "make start",
  "debug": "make debug",
  "test": "make test",
  "test:debug": "make test-debug",
};

const name = process.argv[2];
const insideContainer = process.env.RAYTRACING_IN_CONTAINER === "1";

const result = insideContainer
  ? spawnSync("sh", ["-c", commands[name]], { stdio: "inherit" })
  : spawnSync(
      "docker",
      ["run", "--rm", "-v", `${process.cwd()}:/app`, "raytracing", "npm", "run", name],
      { stdio: "inherit" }
    );

process.exit(result.status ?? 1);
