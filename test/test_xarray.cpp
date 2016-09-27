#include "gtest/gtest.h"
#include "xarray/xarray.hpp"
#include "test_common.hpp"

namespace qs
{
    TEST(xarray, shaped_constructor)
    {
        {
            SCOPED_TRACE("row_major constructor");
            row_major_result rm;
            xarray<int> ra(rm.m_shape);
            compare_shape(ra, rm);
        }
        
        {
            SCOPED_TRACE("column_major constructor");
            column_major_result cm;
            xarray<int> ca(cm.m_shape, layout::column_major);
            compare_shape(ca, cm);
        }
    }

    TEST(xarray, strided_constructor)
    {
        central_major_result cmr;
        xarray<int> cma(cmr.m_shape, cmr.m_strides);
        compare_shape(cma, cmr);
    }

    TEST(xarray, valued_constructor)
    {
        {
            SCOPED_TRACE("row_major valued constructor");
            row_major_result rm;
            int value = 2;
            xarray<int> ra(rm.m_shape, value);
            compare_shape(ra, rm);
            xarray<int>::container_type vec(ra.size(), value);
            EXPECT_EQ(ra.data(), vec);
        }

        {
            SCOPED_TRACE("column_major valued constructor");
            column_major_result cm;
            int value = 2;
            xarray<int> ca(cm.m_shape, value, layout::column_major);
            compare_shape(ca, cm);
            xarray<int>::container_type vec(ca.size(), value);
            EXPECT_EQ(ca.data(), vec);
        }
    }

    TEST(xarray, strided_valued_constructor)
    {
        central_major_result cmr;
        int value = 2;
        xarray<int> cma(cmr.m_shape, cmr.m_strides, value);
        compare_shape(cma, cmr);
        xarray<int>::container_type vec(cma.size(), value);
        EXPECT_EQ(cma.data(), vec);
    }

    TEST(xarray, copy_semantic)
    {
        central_major_result res;
        int value = 2;
        xarray<int> a(res.m_shape, res.m_strides, value);
        
        {
            SCOPED_TRACE("copy constructor");
            xarray<int> b(a);
            compare_shape(a, b);
            EXPECT_EQ(a.data(), b.data());
        }

        {
            SCOPED_TRACE("assignment operator");
            row_major_result r;
            xarray<int> c(r.m_shape, 0);
            EXPECT_NE(a.data(), c.data());
            c = a;
            compare_shape(a, c);
            EXPECT_EQ(a.data(), c.data());
        }
    }

    TEST(xarray, move_semantic)
    {
        central_major_result res;
        int value = 2;
        xarray<int> a(res.m_shape, res.m_strides, value);

        {
            SCOPED_TRACE("move constructor");
            xarray<int> tmp(a);
            xarray<int> b(std::move(tmp));
            compare_shape(a, b);
            EXPECT_EQ(a.data(), b.data());
        }

        {
            SCOPED_TRACE("move assignment");
            row_major_result r;
            xarray<int> c(r.m_shape, 0);
            EXPECT_NE(a.data(), c.data());
            xarray<int> tmp(a);
            c = std::move(tmp);
            compare_shape(a, c);
            EXPECT_EQ(a.data(), c.data());
        }
    }

    TEST(xarray, reshape)
    {
        xarray<int> a;
        test_reshape(a);
    }

    TEST(xarray, access)
    {
        xarray<int> a;
        test_access(a);
    }

    TEST(xarray, broadcast_shape)
    {
        xarray<int> a;
        test_broadcast(a);
    }

    TEST(xarray, storage_iterator)
    {
        xarray<int> a;
        test_storage_iterator(a);
    }

}

