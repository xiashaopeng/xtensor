/***************************************************************************
* Copyright (c) 2016, Johan Mabille, Sylvain Corlay and Wolf Vollprecht    *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

// This file is generated from test/files/cppy_source/test_extended_broadcast_view.cppy by preprocess.py!

#include <algorithm>

#include "gtest/gtest.h"
#include "xtensor/xarray.hpp"
#include "xtensor/xfixed.hpp"
#include "xtensor/xnoalias.hpp"
#include "xtensor/xstrided_view.hpp"
#include "xtensor/xtensor.hpp"
#include "xtensor/xview.hpp"

namespace xt
{
    using namespace xt::placeholders;

    /*py
    a = np.arange(35, dtype=np.float64).reshape(5, 7)
    */
    TEST(xtest_extended, negative_slices_twod)
    {
        // py_a
        xarray<double> py_a = {{ 0., 1., 2., 3., 4., 5., 6.},
                               { 7., 8., 9.,10.,11.,12.,13.},
                               {14.,15.,16.,17.,18.,19.,20.},
                               {21.,22.,23.,24.,25.,26.,27.},
                               {28.,29.,30.,31.,32.,33.,34.}};
        // py_av0 = a[:-2, ::-1]
        xarray<double> py_av0 = {{ 6., 5., 4., 3., 2., 1., 0.},
                                 {13.,12.,11.,10., 9., 8., 7.},
                                 {20.,19.,18.,17.,16.,15.,14.}};
        auto av0 = xt::strided_view(py_a, {_r|_|-2, _r|_|_|-1});
        EXPECT_EQ(av0, py_av0);
        // py_av1 = a[::-1, ::-1]
        xarray<double> py_av1 = {{34.,33.,32.,31.,30.,29.,28.},
                                 {27.,26.,25.,24.,23.,22.,21.},
                                 {20.,19.,18.,17.,16.,15.,14.},
                                 {13.,12.,11.,10., 9., 8., 7.},
                                 { 6., 5., 4., 3., 2., 1., 0.}};
        auto av1 = xt::strided_view(py_a, {_r|_|_|-1, _r|_|_|-1});
        EXPECT_EQ(av1, py_av1);
        // py_av2 = a[1:-3, -3:2:-1]
        xarray<double> py_av2 = {{11.,10.}};
        auto av2 = xt::strided_view(py_a, {_r|1|-3, _r|-3|2|-1});
        EXPECT_EQ(av2, py_av2);
        // py_av3 = a[-1:-4:-1, -3:1:-2]
        xarray<double> py_av3 = {{32.,30.},
                                 {25.,23.},
                                 {18.,16.}};
        auto av3 = xt::strided_view(py_a, {_r|-1|-4|-1, _r|-3|1|-2});
        EXPECT_EQ(av3, py_av3);
        auto av4 = xt::strided_view(py_a, {_r|-3|-5, _r|-3|10});
        EXPECT_EQ(av4.size(), 0);
        // py_av5 = a[-5:-2, -3:10]
        xarray<double> py_av5 = {{ 4., 5., 6.},
                                 {11.,12.,13.},
                                 {18.,19.,20.}};
        auto av5 = xt::strided_view(py_a, {_r|-5|-2, _r|-3|10});
        EXPECT_EQ(av5, py_av5);
    }

    /*py
    a0 = np.arange(35).reshape(5, 7)
    a = np.copy(a0)
    a[0:-2] += a[:3:-1]
    at = np.copy(a)
    at[::-2] += at[::2]
    */
    TEST(xtest_extended, negative_slices_math)
    {
        // py_a0
        xarray<long> py_a0 = {{ 0, 1, 2, 3, 4, 5, 6},
                              { 7, 8, 9,10,11,12,13},
                              {14,15,16,17,18,19,20},
                              {21,22,23,24,25,26,27},
                              {28,29,30,31,32,33,34}};
        strided_view(py_a0, {_r|0|-2}) += strided_view(py_a0, {{_r|_|3|-1}});
        // py_a
        xarray<long> py_a = {{28,30,32,34,36,38,40},
                             {35,37,39,41,43,45,47},
                             {42,44,46,48,50,52,54},
                             {21,22,23,24,25,26,27},
                             {28,29,30,31,32,33,34}};
        EXPECT_EQ(py_a0, py_a);
        strided_view(py_a0, {_r|_|_|-2}) += strided_view(py_a0, {_r|_|_|2});
        // py_at
        xarray<long> py_at = {{ 56, 59, 62, 65, 68, 71, 74},
                              { 35, 37, 39, 41, 43, 45, 47},
                              { 84, 88, 92, 96,100,104,108},
                              { 21, 22, 23, 24, 25, 26, 27},
                              { 56, 59, 62, 65, 68, 71, 74}};
        EXPECT_EQ(py_a0, py_at);
    }

    /*py
    a1 = np.arange(35).reshape(5, 1, 7)
    a2 = np.copy(a).reshape(1, 5, 1, 7)
    a3 = np.array([6,2,3,5,1]).reshape(1, 5, 1, 1)
    a1_a2 = a1 + a2
    b1 = np.arange(7)
    b1_a1 = a1 + b1
    b2 = np.copy(b1).reshape(1, 1, 1, 7)
    a1_b2 = a1 + b2
    b3 = np.random.random((2, 5, 4, 7))
    a2_b3 = a2 + b3
    */
    TEST(xtest_extended, broadcasting)
    {
        // py_a1
        xarray<long> py_a1 = {{{ 0, 1, 2, 3, 4, 5, 6}},
                             
                              {{ 7, 8, 9,10,11,12,13}},
                             
                              {{14,15,16,17,18,19,20}},
                             
                              {{21,22,23,24,25,26,27}},
                             
                              {{28,29,30,31,32,33,34}}};
        // py_a2
        xarray<long> py_a2 = {{{{28,30,32,34,36,38,40}},
                             
                               {{35,37,39,41,43,45,47}},
                             
                               {{42,44,46,48,50,52,54}},
                             
                               {{21,22,23,24,25,26,27}},
                             
                               {{28,29,30,31,32,33,34}}}};
        // py_b1
        xarray<long> py_b1 = {0,1,2,3,4,5,6};
        // py_b2
        xarray<long> py_b2 = {{{{0,1,2,3,4,5,6}}}};
        // py_b3
        xarray<double> py_b3 = {{{{0.90404131,0.63651345,0.59389169,0.06260277,0.4970625 ,0.18399467,
                                   0.2468271 },
                                  {0.36793325,0.24565335,0.99243071,0.78264985,0.90673263,0.97173395,
                                   0.93541472},
                                  {0.09851233,0.30936033,0.54787388,0.83189662,0.7626801 ,0.70153453,
                                   0.81516074},
                                  {0.15364773,0.17031219,0.40295852,0.43052477,0.85447307,0.76115209,
                                   0.3869196 }},
                               
                                 {{0.99926519,0.61007609,0.61273456,0.5572792 ,0.53339686,0.73579692,
                                   0.06081958},
                                  {0.43642265,0.64689219,0.32154917,0.82327591,0.91273714,0.93492972,
                                   0.84840825},
                                  {0.47762574,0.80365408,0.71688222,0.57528924,0.07381368,0.77635397,
                                   0.82954766},
                                  {0.79047938,0.31181656,0.29717277,0.55095625,0.04575194,0.70018578,
                                   0.16907239}},
                               
                                 {{0.43280768,0.71156   ,0.31855035,0.79199498,0.79563348,0.88714674,
                                   0.20359139},
                                  {0.72067261,0.92522158,0.70272621,0.59760313,0.48104425,0.97875074,
                                   0.65655076},
                                  {0.33918421,0.27427356,0.67066822,0.77475433,0.27403743,0.93196448,
                                   0.88875944},
                                  {0.25390781,0.27066673,0.51795101,0.65379245,0.15500522,0.67635568,
                                   0.32031408}},
                               
                                 {{0.20802221,0.99847765,0.73392518,0.09811889,0.22796301,0.82569256,
                                   0.23660129},
                                  {0.13609809,0.73526015,0.38659574,0.5390973 ,0.84199722,0.41359159,
                                   0.51957164},
                                  {0.61249558,0.32499741,0.96142713,0.32068334,0.79211864,0.38927042,
                                   0.03298208},
                                  {0.37471974,0.8383987 ,0.97848196,0.51526679,0.11751935,0.2743507 ,
                                   0.79068148}},
                               
                                 {{0.35302419,0.57316546,0.5630049 ,0.81621397,0.160881  ,0.65003573,
                                   0.87661699},
                                  {0.65033976,0.5940945 ,0.75843266,0.71168427,0.29769762,0.8405908 ,
                                   0.62015098},
                                  {0.73278979,0.32661462,0.59257281,0.90375257,0.86635972,0.60990862,
                                   0.04599801},
                                  {0.84691571,0.15347306,0.5133097 ,0.37169585,0.58300826,0.98984478,
                                   0.52023777}}},
                               
                               
                                {{{0.53139709,0.47489371,0.09430164,0.71863019,0.40926118,0.12454096,
                                   0.7188013 },
                                  {0.12756612,0.97768928,0.58668043,0.6900911 ,0.73486761,0.13042077,
                                   0.4389306 },
                                  {0.57099038,0.28456518,0.51788253,0.62625642,0.81545626,0.02176762,
                                   0.1725162 },
                                  {0.62248903,0.05489784,0.88156656,0.9170209 ,0.78332614,0.12490675,
                                   0.79793203}},
                               
                                 {{0.27894764,0.88605424,0.70924643,0.93327602,0.33310638,0.5991655 ,
                                   0.8617647 },
                                  {0.18416503,0.378891  ,0.64675506,0.83272407,0.41114844,0.11166028,
                                   0.90901016},
                                  {0.3385693 ,0.45241791,0.56580704,0.591283  ,0.22571159,0.0335618 ,
                                   0.03808591},
                                  {0.1214151 ,0.88298236,0.27741279,0.44995171,0.81717776,0.52227008,
                                   0.89158426}},
                               
                                 {{0.37751415,0.15592155,0.56337262,0.88116938,0.16049046,0.32123579,
                                   0.35449713},
                                  {0.7151522 ,0.41047627,0.77970922,0.89533089,0.69715769,0.69543941,
                                   0.52247318},
                                  {0.23334597,0.45931066,0.36808849,0.79479573,0.31286571,0.86514218,
                                   0.95356672},
                                  {0.14683788,0.79607299,0.32544479,0.63654001,0.94889479,0.05159957,
                                   0.94694499}},
                               
                                 {{0.52011363,0.11206203,0.44606523,0.73846263,0.95830185,0.93710375,
                                   0.38663452},
                                  {0.64019931,0.40709309,0.29678573,0.95723415,0.14946191,0.09500027,
                                   0.1492391 },
                                  {0.94430254,0.96850819,0.33664569,0.55244566,0.33058461,0.25667763,
                                   0.94974892},
                                  {0.37505428,0.3665873 ,0.41462322,0.99780559,0.73593391,0.46921396,
                                   0.39117158}},
                               
                                 {{0.32115412,0.50840554,0.93943283,0.64766195,0.796236  ,0.02901594,
                                   0.47561913},
                                  {0.09708499,0.9501679 ,0.87018323,0.8818399 ,0.41362032,0.95405105,
                                   0.14093741},
                                  {0.07118416,0.26836929,0.23612372,0.77766684,0.41481005,0.09376128,
                                   0.27805039},
                                  {0.4811227 ,0.56007129,0.48527345,0.51205981,0.72543368,0.59091214,
                                   0.01564156}}}};
        xt::xarray<long> a1_a2 = py_a1 + py_a2;
        // py_a1_a2
        xarray<long> py_a1_a2 = {{{{28,31,34,37,40,43,46}},
                                
                                  {{42,45,48,51,54,57,60}},
                                
                                  {{56,59,62,65,68,71,74}},
                                
                                  {{42,44,46,48,50,52,54}},
                                
                                  {{56,58,60,62,64,66,68}}}};
        EXPECT_EQ(a1_a2, py_a1_a2);

        xt::xarray<long> b1_a1 = py_b1 + py_a1;
        // py_b1_a1
        xarray<long> py_b1_a1 = {{{ 0, 2, 4, 6, 8,10,12}},
                                
                                 {{ 7, 9,11,13,15,17,19}},
                                
                                 {{14,16,18,20,22,24,26}},
                                
                                 {{21,23,25,27,29,31,33}},
                                
                                 {{28,30,32,34,36,38,40}}};
        EXPECT_EQ(b1_a1, py_b1_a1);

        xt::xarray<long> a1_b2 = py_a1 + py_b2;
        // py_a1_b2
        xarray<long> py_a1_b2 = {{{{ 0, 2, 4, 6, 8,10,12}},
                                
                                  {{ 7, 9,11,13,15,17,19}},
                                
                                  {{14,16,18,20,22,24,26}},
                                
                                  {{21,23,25,27,29,31,33}},
                                
                                  {{28,30,32,34,36,38,40}}}};
        EXPECT_EQ(a1_b2, py_a1_b2);

        xt::xarray<double> a2_b3 = xt::cast<double>(py_a2) + py_b3;
        // py_a2_b3
        xarray<double> py_a2_b3 = {{{{28.90404131,30.63651345,32.59389169,34.06260277,36.4970625 ,
                                      38.18399467,40.2468271 },
                                     {28.36793325,30.24565335,32.99243071,34.78264985,36.90673263,
                                      38.97173395,40.93541472},
                                     {28.09851233,30.30936033,32.54787388,34.83189662,36.7626801 ,
                                      38.70153453,40.81516074},
                                     {28.15364773,30.17031219,32.40295852,34.43052477,36.85447307,
                                      38.76115209,40.3869196 }},
                                  
                                    {{35.99926519,37.61007609,39.61273456,41.5572792 ,43.53339686,
                                      45.73579692,47.06081958},
                                     {35.43642265,37.64689219,39.32154917,41.82327591,43.91273714,
                                      45.93492972,47.84840825},
                                     {35.47762574,37.80365408,39.71688222,41.57528924,43.07381368,
                                      45.77635397,47.82954766},
                                     {35.79047938,37.31181656,39.29717277,41.55095625,43.04575194,
                                      45.70018578,47.16907239}},
                                  
                                    {{42.43280768,44.71156   ,46.31855035,48.79199498,50.79563348,
                                      52.88714674,54.20359139},
                                     {42.72067261,44.92522158,46.70272621,48.59760313,50.48104425,
                                      52.97875074,54.65655076},
                                     {42.33918421,44.27427356,46.67066822,48.77475433,50.27403743,
                                      52.93196448,54.88875944},
                                     {42.25390781,44.27066673,46.51795101,48.65379245,50.15500522,
                                      52.67635568,54.32031408}},
                                  
                                    {{21.20802221,22.99847765,23.73392518,24.09811889,25.22796301,
                                      26.82569256,27.23660129},
                                     {21.13609809,22.73526015,23.38659574,24.5390973 ,25.84199722,
                                      26.41359159,27.51957164},
                                     {21.61249558,22.32499741,23.96142713,24.32068334,25.79211864,
                                      26.38927042,27.03298208},
                                     {21.37471974,22.8383987 ,23.97848196,24.51526679,25.11751935,
                                      26.2743507 ,27.79068148}},
                                  
                                    {{28.35302419,29.57316546,30.5630049 ,31.81621397,32.160881  ,
                                      33.65003573,34.87661699},
                                     {28.65033976,29.5940945 ,30.75843266,31.71168427,32.29769762,
                                      33.8405908 ,34.62015098},
                                     {28.73278979,29.32661462,30.59257281,31.90375257,32.86635972,
                                      33.60990862,34.04599801},
                                     {28.84691571,29.15347306,30.5133097 ,31.37169585,32.58300826,
                                      33.98984478,34.52023777}}},
                                  
                                  
                                   {{{28.53139709,30.47489371,32.09430164,34.71863019,36.40926118,
                                      38.12454096,40.7188013 },
                                     {28.12756612,30.97768928,32.58668043,34.6900911 ,36.73486761,
                                      38.13042077,40.4389306 },
                                     {28.57099038,30.28456518,32.51788253,34.62625642,36.81545626,
                                      38.02176762,40.1725162 },
                                     {28.62248903,30.05489784,32.88156656,34.9170209 ,36.78332614,
                                      38.12490675,40.79793203}},
                                  
                                    {{35.27894764,37.88605424,39.70924643,41.93327602,43.33310638,
                                      45.5991655 ,47.8617647 },
                                     {35.18416503,37.378891  ,39.64675506,41.83272407,43.41114844,
                                      45.11166028,47.90901016},
                                     {35.3385693 ,37.45241791,39.56580704,41.591283  ,43.22571159,
                                      45.0335618 ,47.03808591},
                                     {35.1214151 ,37.88298236,39.27741279,41.44995171,43.81717776,
                                      45.52227008,47.89158426}},
                                  
                                    {{42.37751415,44.15592155,46.56337262,48.88116938,50.16049046,
                                      52.32123579,54.35449713},
                                     {42.7151522 ,44.41047627,46.77970922,48.89533089,50.69715769,
                                      52.69543941,54.52247318},
                                     {42.23334597,44.45931066,46.36808849,48.79479573,50.31286571,
                                      52.86514218,54.95356672},
                                     {42.14683788,44.79607299,46.32544479,48.63654001,50.94889479,
                                      52.05159957,54.94694499}},
                                  
                                    {{21.52011363,22.11206203,23.44606523,24.73846263,25.95830185,
                                      26.93710375,27.38663452},
                                     {21.64019931,22.40709309,23.29678573,24.95723415,25.14946191,
                                      26.09500027,27.1492391 },
                                     {21.94430254,22.96850819,23.33664569,24.55244566,25.33058461,
                                      26.25667763,27.94974892},
                                     {21.37505428,22.3665873 ,23.41462322,24.99780559,25.73593391,
                                      26.46921396,27.39117158}},
                                  
                                    {{28.32115412,29.50840554,30.93943283,31.64766195,32.796236  ,
                                      33.02901594,34.47561913},
                                     {28.09708499,29.9501679 ,30.87018323,31.8818399 ,32.41362032,
                                      33.95405105,34.14093741},
                                     {28.07118416,29.26836929,30.23612372,31.77766684,32.41481005,
                                      33.09376128,34.27805039},
                                     {28.4811227 ,29.56007129,30.48527345,31.51205981,32.72543368,
                                      33.59091214,34.01564156}}}};
        EXPECT_TRUE(xt::allclose(a2_b3, py_a2_b3));
    }

    /*py
    a0 = np.arange(5 * 3 * 7).reshape(5, 3, 7)
    a1 = np.copy(a0)
    b1 = np.arange(5 * 3).reshape(5, 3)
    a1[:, :, 2] = b1
    a2 = np.copy(a1)
    ar2 = np.arange(35).reshape(5, 1, 7)
    a1[:, 0, np.newaxis, :] = ar2
    a3 = np.copy(a1)
    a1[:, 2, :] = np.arange(7)
    a4 = np.copy(a1)
    ax1 = np.copy(a0)
    ax1[1, :, :] = -1
    ax2 = np.copy(a0)
    ax2[0:2, 0:2, :] = -1
    ax3 = np.copy(a0)
    ax3[1, 0:2:2, :] = -1
    ax4 = np.copy(a0)
    ax4[:, 0:2, :] = -1
    */
    TEST(xtest_extended, broadcast_into_view)
    {
        // py_a0
        xarray<long> py_a0 = {{{  0,  1,  2,  3,  4,  5,  6},
                               {  7,  8,  9, 10, 11, 12, 13},
                               { 14, 15, 16, 17, 18, 19, 20}},
                             
                              {{ 21, 22, 23, 24, 25, 26, 27},
                               { 28, 29, 30, 31, 32, 33, 34},
                               { 35, 36, 37, 38, 39, 40, 41}},
                             
                              {{ 42, 43, 44, 45, 46, 47, 48},
                               { 49, 50, 51, 52, 53, 54, 55},
                               { 56, 57, 58, 59, 60, 61, 62}},
                             
                              {{ 63, 64, 65, 66, 67, 68, 69},
                               { 70, 71, 72, 73, 74, 75, 76},
                               { 77, 78, 79, 80, 81, 82, 83}},
                             
                              {{ 84, 85, 86, 87, 88, 89, 90},
                               { 91, 92, 93, 94, 95, 96, 97},
                               { 98, 99,100,101,102,103,104}}};
        xt::xarray<long> a = py_a0;

        // py_b1
        xarray<long> py_b1 = {{ 0, 1, 2},
                              { 3, 4, 5},
                              { 6, 7, 8},
                              { 9,10,11},
                              {12,13,14}};
        // py_a2
        xarray<long> py_a2 = {{{  0,  1,  0,  3,  4,  5,  6},
                               {  7,  8,  1, 10, 11, 12, 13},
                               { 14, 15,  2, 17, 18, 19, 20}},
                             
                              {{ 21, 22,  3, 24, 25, 26, 27},
                               { 28, 29,  4, 31, 32, 33, 34},
                               { 35, 36,  5, 38, 39, 40, 41}},
                             
                              {{ 42, 43,  6, 45, 46, 47, 48},
                               { 49, 50,  7, 52, 53, 54, 55},
                               { 56, 57,  8, 59, 60, 61, 62}},
                             
                              {{ 63, 64,  9, 66, 67, 68, 69},
                               { 70, 71, 10, 73, 74, 75, 76},
                               { 77, 78, 11, 80, 81, 82, 83}},
                             
                              {{ 84, 85, 12, 87, 88, 89, 90},
                               { 91, 92, 13, 94, 95, 96, 97},
                               { 98, 99, 14,101,102,103,104}}};
        view(a, all(), all(), 2) = py_b1;
        EXPECT_EQ(a, py_a2);

        // py_ar2
        xarray<long> py_ar2 = {{{ 0, 1, 2, 3, 4, 5, 6}},
                              
                               {{ 7, 8, 9,10,11,12,13}},
                              
                               {{14,15,16,17,18,19,20}},
                              
                               {{21,22,23,24,25,26,27}},
                              
                               {{28,29,30,31,32,33,34}}};
        xt::xarray<long> ar2 = py_ar2;
        view(a, all(), 0, newaxis(), all()) = ar2;

        // py_a3
        xarray<long> py_a3 = {{{  0,  1,  2,  3,  4,  5,  6},
                               {  7,  8,  1, 10, 11, 12, 13},
                               { 14, 15,  2, 17, 18, 19, 20}},
                             
                              {{  7,  8,  9, 10, 11, 12, 13},
                               { 28, 29,  4, 31, 32, 33, 34},
                               { 35, 36,  5, 38, 39, 40, 41}},
                             
                              {{ 14, 15, 16, 17, 18, 19, 20},
                               { 49, 50,  7, 52, 53, 54, 55},
                               { 56, 57,  8, 59, 60, 61, 62}},
                             
                              {{ 21, 22, 23, 24, 25, 26, 27},
                               { 70, 71, 10, 73, 74, 75, 76},
                               { 77, 78, 11, 80, 81, 82, 83}},
                             
                              {{ 28, 29, 30, 31, 32, 33, 34},
                               { 91, 92, 13, 94, 95, 96, 97},
                               { 98, 99, 14,101,102,103,104}}};
        EXPECT_EQ(a, py_a3);

        view(a, all(), 2, all()) = xt::arange(7);
        // py_a4
        xarray<long> py_a4 = {{{ 0, 1, 2, 3, 4, 5, 6},
                               { 7, 8, 1,10,11,12,13},
                               { 0, 1, 2, 3, 4, 5, 6}},
                             
                              {{ 7, 8, 9,10,11,12,13},
                               {28,29, 4,31,32,33,34},
                               { 0, 1, 2, 3, 4, 5, 6}},
                             
                              {{14,15,16,17,18,19,20},
                               {49,50, 7,52,53,54,55},
                               { 0, 1, 2, 3, 4, 5, 6}},
                             
                              {{21,22,23,24,25,26,27},
                               {70,71,10,73,74,75,76},
                               { 0, 1, 2, 3, 4, 5, 6}},
                             
                              {{28,29,30,31,32,33,34},
                               {91,92,13,94,95,96,97},
                               { 0, 1, 2, 3, 4, 5, 6}}};
        EXPECT_EQ(a, py_a4);

        a = py_a0;
        view(a, 1, all(), all()) = -1;

        // py_ax1
        xarray<long> py_ax1 = {{{  0,  1,  2,  3,  4,  5,  6},
                                {  7,  8,  9, 10, 11, 12, 13},
                                { 14, 15, 16, 17, 18, 19, 20}},
                              
                               {{ -1, -1, -1, -1, -1, -1, -1},
                                { -1, -1, -1, -1, -1, -1, -1},
                                { -1, -1, -1, -1, -1, -1, -1}},
                              
                               {{ 42, 43, 44, 45, 46, 47, 48},
                                { 49, 50, 51, 52, 53, 54, 55},
                                { 56, 57, 58, 59, 60, 61, 62}},
                              
                               {{ 63, 64, 65, 66, 67, 68, 69},
                                { 70, 71, 72, 73, 74, 75, 76},
                                { 77, 78, 79, 80, 81, 82, 83}},
                              
                               {{ 84, 85, 86, 87, 88, 89, 90},
                                { 91, 92, 93, 94, 95, 96, 97},
                                { 98, 99,100,101,102,103,104}}};
        EXPECT_EQ(a, py_ax1);

        a = py_a0;
        view(a, range(0, 2), range(0, 2), all()) = -1;

        // py_ax2
        xarray<long> py_ax2 = {{{ -1, -1, -1, -1, -1, -1, -1},
                                { -1, -1, -1, -1, -1, -1, -1},
                                { 14, 15, 16, 17, 18, 19, 20}},
                              
                               {{ -1, -1, -1, -1, -1, -1, -1},
                                { -1, -1, -1, -1, -1, -1, -1},
                                { 35, 36, 37, 38, 39, 40, 41}},
                              
                               {{ 42, 43, 44, 45, 46, 47, 48},
                                { 49, 50, 51, 52, 53, 54, 55},
                                { 56, 57, 58, 59, 60, 61, 62}},
                              
                               {{ 63, 64, 65, 66, 67, 68, 69},
                                { 70, 71, 72, 73, 74, 75, 76},
                                { 77, 78, 79, 80, 81, 82, 83}},
                              
                               {{ 84, 85, 86, 87, 88, 89, 90},
                                { 91, 92, 93, 94, 95, 96, 97},
                                { 98, 99,100,101,102,103,104}}};
        EXPECT_EQ(a, py_ax2);

        a = py_a0;
        view(a, all(), range(0, 2), all()) = -1;
        // py_ax4
        xarray<long> py_ax4 = {{{ -1, -1, -1, -1, -1, -1, -1},
                                { -1, -1, -1, -1, -1, -1, -1},
                                { 14, 15, 16, 17, 18, 19, 20}},
                              
                               {{ -1, -1, -1, -1, -1, -1, -1},
                                { -1, -1, -1, -1, -1, -1, -1},
                                { 35, 36, 37, 38, 39, 40, 41}},
                              
                               {{ -1, -1, -1, -1, -1, -1, -1},
                                { -1, -1, -1, -1, -1, -1, -1},
                                { 56, 57, 58, 59, 60, 61, 62}},
                              
                               {{ -1, -1, -1, -1, -1, -1, -1},
                                { -1, -1, -1, -1, -1, -1, -1},
                                { 77, 78, 79, 80, 81, 82, 83}},
                              
                               {{ -1, -1, -1, -1, -1, -1, -1},
                                { -1, -1, -1, -1, -1, -1, -1},
                                { 98, 99,100,101,102,103,104}}};
        EXPECT_EQ(a, py_ax4);

        a = py_a0;
        view(a, 1, range(0, 2, 2), all()) = -1;
        // py_ax3
        xarray<long> py_ax3 = {{{  0,  1,  2,  3,  4,  5,  6},
                                {  7,  8,  9, 10, 11, 12, 13},
                                { 14, 15, 16, 17, 18, 19, 20}},
                              
                               {{ -1, -1, -1, -1, -1, -1, -1},
                                { 28, 29, 30, 31, 32, 33, 34},
                                { 35, 36, 37, 38, 39, 40, 41}},
                              
                               {{ 42, 43, 44, 45, 46, 47, 48},
                                { 49, 50, 51, 52, 53, 54, 55},
                                { 56, 57, 58, 59, 60, 61, 62}},
                              
                               {{ 63, 64, 65, 66, 67, 68, 69},
                                { 70, 71, 72, 73, 74, 75, 76},
                                { 77, 78, 79, 80, 81, 82, 83}},
                              
                               {{ 84, 85, 86, 87, 88, 89, 90},
                                { 91, 92, 93, 94, 95, 96, 97},
                                { 98, 99,100,101,102,103,104}}};
        EXPECT_EQ(a, py_ax3);
    }

    /*py
    a0 = np.arange(2 * 3 * 4).reshape(2, 3, 4)
    a1 = np.arange(3 * 4).reshape(3, 4)
    a2 = np.arange(2 * 4).reshape(2, 1, 4)
    a3 = np.arange(4).reshape(1, 1, 4)
    a4 = np.arange(3 * 1).reshape(3, 1)
    # test 1
    a0_cp1 = np.copy(a0)
    a0_cp1[0:2, :, :] = a0 * 2 + a4
    a0_cp2 = np.copy(a0_cp1)
    a0_cp2[0, :, :] *= a1 * 7 + a4
    
    x0 = np.arange(3 * 3 * 2).reshape(3, 3, 2)
    a0_cp3 = np.copy(a0_cp2)
    a0_cp3[0, :, ::2] = x0[1, :, :]
    */
    TEST(xtest_extended, broadcast_funcs_view)
    {
        // py_a0
        xarray<long> py_a0 = {{{ 0, 1, 2, 3},
                               { 4, 5, 6, 7},
                               { 8, 9,10,11}},
                             
                              {{12,13,14,15},
                               {16,17,18,19},
                               {20,21,22,23}}};
        // py_a1
        xarray<long> py_a1 = {{ 0, 1, 2, 3},
                              { 4, 5, 6, 7},
                              { 8, 9,10,11}};
        // py_a2
        xarray<long> py_a2 = {{{0,1,2,3}},
                             
                              {{4,5,6,7}}};
        // py_a3
        xarray<long> py_a3 = {{{0,1,2,3}}};
        xt::xarray<long> py_a4 = {0, 1, 2};
        py_a4.reshape({3, 1});

        xt::xarray<long> a = py_a0;
        xt::view(a, range(0, 2), all(), all()) = py_a0 * 2 + py_a4;
        // py_a0_cp1
        xarray<long> py_a0_cp1 = {{{ 0, 2, 4, 6},
                                   { 9,11,13,15},
                                   {18,20,22,24}},
                                 
                                  {{24,26,28,30},
                                   {33,35,37,39},
                                   {42,44,46,48}}};
        EXPECT_EQ(py_a0_cp1, a);

        // py_a0_cp2
        xarray<long> py_a0_cp2 = {{{   0,  14,  56, 126},
                                   { 261, 396, 559, 750},
                                   {1044,1300,1584,1896}},
                                 
                                  {{  24,  26,  28,  30},
                                   {  33,  35,  37,  39},
                                   {  42,  44,  46,  48}}};
        xt::view(a, 0, all(), all()) *= py_a1 * 7 + py_a4;
        EXPECT_EQ(py_a0_cp2, a);
        
        // py_x0
        xarray<long> py_x0 = {{{ 0, 1},
                               { 2, 3},
                               { 4, 5}},
                             
                              {{ 6, 7},
                               { 8, 9},
                               {10,11}},
                             
                              {{12,13},
                               {14,15},
                               {16,17}}};
        // py_a0_cp3
        xarray<long> py_a0_cp3 = {{{   6,  14,   7, 126},
                                   {   8, 396,   9, 750},
                                   {  10,1300,  11,1896}},
                                 
                                  {{  24,  26,  28,  30},
                                   {  33,  35,  37,  39},
                                   {  42,  44,  46,  48}}};
        xt::view(a, 0, all(), range(_, _, 2)) = xt::view(py_x0, 1, all(), all());
        EXPECT_EQ(a, py_a0_cp3);

        xt::view(a, 0, all(), all()) = xt::view((py_a0 * py_a0 + 3), 0, all(), all());
        // py_x1 = (a0 * a0 + 3)[0, :, :]
        xarray<long> py_x1 = {{  3,  4,  7, 12},
                              { 19, 28, 39, 52},
                              { 67, 84,103,124}};
        EXPECT_EQ(py_x1, view(a, 0, all(), all()));
    }
}
