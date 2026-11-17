const { spawnSync } = require("child_process");

const commands = {
  "build:release": "cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release && cmake --build build/release",
  "build:debug": "cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug && cmake --build build/debug",
  "start": "npm run build:release && ./build/release/raytracer",
  "debug": "npm run build:debug && ./build/debug/raytracer",
  "test": "npm run build:release && ctest --test-dir build/release --output-on-failure",
  "test:debug": "npm run build:debug && ctest --test-dir build/debug --output-on-failure",
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
