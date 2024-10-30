#include <omp.h>
#include <cinttypes>
#include <fstream>
#include "hit.h"
#include "parser.h"

class LCG {
public:
    LCG(uint64_t seed = 1) : state(seed) {}

    float next_float(float min, float max) {
        state = (state * 6364136223846793005ULL + 1) % (1ULL << 32);
        return min + (max - min) * (static_cast<float>(state) / static_cast<float>(1ULL << 32));
    }

private:
    uint64_t state;
};

struct thread_data {
    thread_data(int seed) : lcg(seed) {}

    LCG lcg;
    uint64_t local_count = 0;

    uint8_t padding[64 - sizeof(lcg) - sizeof(uint64_t)];
};

void run(arguments args){
    uint64_t num_points;
    uint64_t points_inside = 0;

    std::ifstream in(args.input_file);
    in >> num_points;
    in.close();

    if (args.isOmp) {
        auto start = omp_get_wtime();

        if (!args.isDefault) {
            if (args.threads == 0) {
                int num_threads = omp_get_max_threads();
                omp_set_num_threads(num_threads);
            } else {
                omp_set_num_threads(args.threads);
            }
        }

        const float *range = get_axis_range();
        const float x_min = range[0];
        const float x_max = range[1];
        const float y_min = range[2];
        const float y_max = range[3];
        const float z_min = range[4];
        const float z_max = range[5];


#pragma omp parallel
        {
            auto td = thread_data(omp_get_thread_num() + 1);

#pragma omp for schedule(dynamic, 10000) nowait
            for (uint64_t i = 0; i < num_points; ++i) {
                float x = td.lcg.next_float(x_min, x_max);
                float y = td.lcg.next_float(y_min, y_max);
                float z = td.lcg.next_float(z_min, z_max);

                if (hit_test(x, y, z)) {
                    ++td.local_count;
                }
            }

#pragma omp atomic
            points_inside += td.local_count;
        }

        float volume_bbox = (x_max - x_min) * (y_max - y_min) * (z_max - z_min);
        float volume_figure = volume_bbox * static_cast<float>(points_inside) / static_cast<float>(num_points);

        auto end = omp_get_wtime();

        printf("Time (%i thread(s)): %g ms\n", (args.threads == 0) ? omp_get_max_threads() : args.threads,
               (end - start) * 1000.f);

        FILE *outf = fopen(args.output_file, "w");
        fprintf(outf, "%g\n", volume_figure);
        fclose(outf);
    } else {
        auto start = omp_get_wtime();

        const float *range = get_axis_range();
        const float x_min = range[0];
        const float x_max = range[1];
        const float y_min = range[2];
        const float y_max = range[3];
        const float z_min = range[4];
        const float z_max = range[5];

        LCG lcg;

        for (uint64_t i = 0; i < num_points; ++i) {
            float x = lcg.next_float(x_min, x_max);
            float y = lcg.next_float(y_min, y_max);
            float z = lcg.next_float(z_min, z_max);

            if (hit_test(x, y, z)) {
                ++points_inside;
            }
        }

        float volume_bbox = (x_max - x_min) * (y_max - y_min) * (z_max - z_min);
        float volume_figure = volume_bbox * static_cast<float>(points_inside) / static_cast<float>(num_points);

        auto end = omp_get_wtime();

        printf("Time (%i thread(s)): %g ms\n", 0, (end - start) * 1000.f);

        FILE *outf = fopen(args.output_file, "w");
        fprintf(outf, "%g\n", volume_figure);
        fclose(outf);
    }
}

int main(int argc, char *argv[]) {
    arguments args = parse(argc, argv);

    run(args);

    return 0;
}
