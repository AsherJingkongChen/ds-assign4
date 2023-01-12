#include "../src/graph/graph.hpp"
#include "../src/tool/tool.hpp"
#include "../src/math/math.hpp"
#include "../src/xml/xml.hpp"

#define RNG_SEED 14641

#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <random>

using namespace xml::tag;
using namespace graph::extra::io;

using us_graph =
  graph::simple_graph<
    uint16_t,
    uint32_t,
    graph::tag::undirected
  >;

using cnt_t     = std::size_t;
using idx_t     = us_graph::index_type;
using len_t     = us_graph::length_type;
using vec2      = math::vec2;
using vec2_list = us_graph::node_list<vec2>;

template<typename _IntTp>
using dist = std::uniform_int_distribution<_IntTp>;

int main(int argc, const char* argv[]) {
  std::ofstream
  fout_svg(
    "output/g_n-1000_x-100_y-100.svg"
  );

  // parameters and structures
  //
  const std::mt19937::result_type
  SEED (
#ifdef RNG_SEED
    RNG_SEED
#else
    std::random_device{}()
#endif // RNG_SEED
  );

  std::mt19937 rng (SEED);
  const cnt_t  N   (1000);
  const cnt_t  X   (100);
  const len_t  Y   (100);

  // (1280 720), (1920, 1080), (3840, 2160), (7680, 4320)
  //
  const float  W   (3840);
  const float  H   (2160);
  const float  WH_R(W / H);
  const vec2   C   (W / 2, H / 2);
  const float  C_R (H / 2.0F / N);
  const float  L_W (C_R / 2.0F);
  const float  R   (H / 2 - C_R - L_W - (W + H) / 200);

  us_graph  g;
  vec2_list s;

  // build g, an undirected graph
  // with 1000 vertices and 1000 + X edges
  //
  for (auto i(N); i--;) {
    g.insert(i, (i + 1) % N, 1);

    // build s, a vec2 list recording the positions of vertex
    //
    vec2 v(math::polar(R, (i + 0.75F) / N));
    v.x() *= WH_R;
    s[i] = C + v;
  }

  for (auto i(X); i--;) {
    auto src = dist<idx_t>(0, N - 1)(rng);
    auto tar = dist<idx_t>(0, N - 1)(rng);

    if (not g.insert(src, tar, Y).second) {
      i++; continue;
    }
  }

  auto scene = xml::element<svg>::get();
  scene->fill         = "gray";
  scene->stroke       = "gray";
  scene->stroke_width = std::to_string(L_W);
  xml::element<svg>::get(scene)->width  = std::to_string(W);
  xml::element<svg>::get(scene)->height = std::to_string(H);

  // edges
  //
  for (auto &e: g) {
    auto l = xml::element<line>::get();
    xml::element<line>::get(l)->x1 = s[e.source()].x_str();
    xml::element<line>::get(l)->y1 = s[e.source()].y_str();
    xml::element<line>::get(l)->x2 = s[e.target()].x_str();
    xml::element<line>::get(l)->y2 = s[e.target()].y_str();

    scene->children.push_back(l);
  }

  // nodes
  //
  auto nodes(g.sources());
  for (auto &p: g.targets()) {
    nodes.insert(p);
  }

  for (auto &p: nodes) {
    auto c = xml::element<circle>::get();
    xml::element<circle>::get(c)->cx = s[p.first].x_str();
    xml::element<circle>::get(c)->cy = s[p.first].y_str();
    xml::element<circle>::get(c)->r  = std::to_string(C_R);

    auto t = xml::element<text>::get();
    xml::element<text>::get(t)->x = s[p.first].x_str();
    xml::element<text>::get(t)->y = s[p.first].y_str();
    xml::element<text>::get(t)->font_family = "Monaco";
    xml::element<text>::get(t)->font_weight = "bold";
    xml::element<text>::get(t)->text_anchor = "middle";
    xml::element<text>::get(t)->font_size   = std::to_string(C_R / 1.25F);

    c->fill         = "black";
    c->stroke_width = "0";

    t->fill         = "white";
    t->stroke_width = "0";
    t->text         = std::to_string(p.first);

    scene->children.push_back(c);
    scene->children.push_back(t);
  }

  // output as svg file
  //
  fout_svg << xml::declaration() << scene->to_string();

  static_assert(N > 2,
    "N should be greater than or equal to 2"
  );
}

// [NOTE]
// - N = 1000
// - X = 100
// - Y = 100
// - all 1000 nodes has an index in [0, 999]
// - X + 1000 edges are added
// - X edges are added randomly
// - S edges are sampled randomly
//
// [SPECIFICATION]
//
// # Study the Properties of "Small World" and Compare Different Data Structures
// 
// *Due: 1/17 23:59:59*
// 
// 1. Generate a cycle of 1000 nodes. Each edge has length 1.
// 2. Add X random edges. Each random edge has the same length Y. 
// 3. Sample Z pairs of source and destination, and compute the average shortest distance (D) of these Z source-destination pairs.
// 
// You need to use 2 different structures of heaps. **(In the report, give the name of the data structures that you use, e.g., array and binomial heap).**
// 
// **Your report should contain:**
// 
// 1. A picture of the graph with X = 100.
// 2. Responses to the following questions: 
//     - What is the relationship between X and D? 
//     - What is the relationship between Y and D?
//     - How to choose Z to obtain a reasonable approximation of the true average shortest distance between all pairs of source and destination?
//     - Which implementation of Dijkstra's Algorithm is faster?
// 
// **You need to support your answers with experimental results.** 
// **You also need to explain how you obtain the results.**
//