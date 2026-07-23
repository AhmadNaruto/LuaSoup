#include "nrp/core/runtime.hpp"
#include "nrp/luau/luau_engine.hpp"
#include "nrp/modules/html.hpp"
#include "nrp/modules/json.hpp"
#include "nrp/modules/crypto.hpp"
#include "nrp/modules/buffer.hpp"
#include <iostream>
#include <chrono>
#include <vector>
#include <iomanip>

class BenchmarkTimer {
    std::chrono::high_resolution_clock::time_point start_time;
public:
    void start() {
        start_time = std::chrono::high_resolution_clock::now();
    }
    double elapsed_ms() const {
        auto end_time = std::chrono::high_resolution_clock::now();
        return std::chrono::duration<double, std::milli>(end_time - start_time).count();
    }
};

void benchmark_zero_copy_buffer() {
    std::cout << "\n[1/5] Benchmarking Zero-Copy Memory & Buffer Throughput..." << std::endl;
    constexpr size_t ITERATIONS = 100000;
    constexpr size_t BUFFER_SIZE = 1024; // 1 KB
    BenchmarkTimer timer;
    timer.start();

    for (size_t i = 0; i < ITERATIONS; ++i) {
        nrp::modules::buffer::Buffer buf(BUFFER_SIZE);
        uint8_t* ptr = buf.data();
        ptr[0] = static_cast<uint8_t>(i & 0xFF);
        ptr[BUFFER_SIZE - 1] = static_cast<uint8_t>((i >> 8) & 0xFF);
    }

    double total_ms = timer.elapsed_ms();
    double total_bytes = static_cast<double>(ITERATIONS * BUFFER_SIZE);
    double mb_per_sec = (total_bytes / (1024.0 * 1024.0)) / (total_ms / 1000.0);
    double ops_per_sec = (ITERATIONS / total_ms) * 1000.0;

    std::cout << "  - Executed " << ITERATIONS << " buffer allocations (1KB each) in " 
              << std::fixed << std::setprecision(2) << total_ms << " ms" << std::endl;
    std::cout << "  - Throughput: " << mb_per_sec << " MB/s (" 
              << static_cast<uint64_t>(ops_per_sec) << " ops/sec)" << std::endl;
}

void benchmark_luau_engine() {
    std::cout << "\n[2/5] Benchmarking Luau Script Execution Speed..." << std::endl;
    nrp::luau::LuauEngine engine;
    engine.initialize();

    constexpr size_t ITERATIONS = 50000;
    const std::string script = "local sum = 0; for i = 1, 100 do sum = sum + i end return sum";

    BenchmarkTimer timer;
    timer.start();

    for (size_t i = 0; i < ITERATIONS; ++i) {
        auto res = engine.eval(script);
        (void)res;
    }

    double total_ms = timer.elapsed_ms();
    double ops_per_sec = (ITERATIONS / total_ms) * 1000.0;

    std::cout << "  - Executed " << ITERATIONS << " sandboxed Luau loop scripts in " 
              << std::fixed << std::setprecision(2) << total_ms << " ms" << std::endl;
    std::cout << "  - Throughput: " << static_cast<uint64_t>(ops_per_sec) << " Luau scripts/sec" << std::endl;
}

void benchmark_html_parser() {
    std::cout << "\n[3/5] Benchmarking HTML/DOM Parsing & CSS Selectors..." << std::endl;
    const std::string sample_html = 
        "<html><head><title>Test Page</title></head><body>"
        "<div class='container'><ul class='list'>"
        "<li class='item'>Item 1</li><li class='item'>Item 2</li><li class='item'>Item 3</li>"
        "</ul></div></body></html>";

    constexpr size_t ITERATIONS = 10000;
    BenchmarkTimer timer;
    timer.start();

    size_t found_count = 0;
    for (size_t i = 0; i < ITERATIONS; ++i) {
        auto doc = nrp::modules::html::Document::parse(sample_html);
        auto node = doc->select_first(".item");
        if (node) {
            found_count++;
        }
    }

    double total_ms = timer.elapsed_ms();
    double docs_per_sec = (ITERATIONS / total_ms) * 1000.0;

    std::cout << "  - Parsed & queried " << ITERATIONS << " HTML documents in " 
              << std::fixed << std::setprecision(2) << total_ms << " ms (found " << found_count << " elements)" << std::endl;
    std::cout << "  - Throughput: " << static_cast<uint64_t>(docs_per_sec) << " docs/sec" << std::endl;
}

void benchmark_json_parser() {
    std::cout << "\n[4/5] Benchmarking JSON Parsing & Serialization..." << std::endl;
    const std::string sample_json = 
        "{\"id\": 1001, \"name\": \"LuaSoup NRP\", \"tags\": [\"cpp20\", \"luau\", \"kotlin\"], \"active\": true}";

    constexpr size_t ITERATIONS = 20000;
    BenchmarkTimer timer;
    timer.start();

    for (size_t i = 0; i < ITERATIONS; ++i) {
        auto val = nrp::modules::json::Json::parse(sample_json);
        std::string serialized = nrp::modules::json::Json::stringify(val);
        (void)serialized;
    }

    double total_ms = timer.elapsed_ms();
    double ops_per_sec = (ITERATIONS / total_ms) * 1000.0;

    std::cout << "  - Parsed & serialized " << ITERATIONS << " JSON objects in " 
              << std::fixed << std::setprecision(2) << total_ms << " ms" << std::endl;
    std::cout << "  - Throughput: " << static_cast<uint64_t>(ops_per_sec) << " JSON ops/sec" << std::endl;
}

void benchmark_crypto() {
    std::cout << "\n[5/5] Benchmarking Cryptographic SHA256 Hashing..." << std::endl;
    const std::string payload(4096, 'A'); // 4 KB payload

    constexpr size_t ITERATIONS = 20000;
    BenchmarkTimer timer;
    timer.start();

    for (size_t i = 0; i < ITERATIONS; ++i) {
        std::string hash = nrp::modules::crypto::Crypto::sha256(payload);
        (void)hash;
    }

    double total_ms = timer.elapsed_ms();
    double total_bytes = static_cast<double>(ITERATIONS * payload.size());
    double mb_per_sec = (total_bytes / (1024.0 * 1024.0)) / (total_ms / 1000.0);

    std::cout << "  - Hashed " << ITERATIONS << " payloads (4KB each) in " 
              << std::fixed << std::setprecision(2) << total_ms << " ms" << std::endl;
    std::cout << "  - Throughput: " << mb_per_sec << " MB/s SHA256 hashing speed" << std::endl;
}

int main() {
    std::cout << "========================================================" << std::endl;
    std::cout << "      LuaSoup NRP Performance Benchmark Suite" << std::endl;
    std::cout << "========================================================" << std::endl;

    benchmark_zero_copy_buffer();
    benchmark_luau_engine();
    benchmark_html_parser();
    benchmark_json_parser();
    benchmark_crypto();

    std::cout << "\n========================================================" << std::endl;
    std::cout << "      Benchmark Suite Completed Successfully!" << std::endl;
    std::cout << "========================================================" << std::endl;
    return 0;
}
