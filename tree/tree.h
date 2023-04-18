//
// Created by USER on 18/04/2023.
//

#pragma once
#include <memory>
#include <optional>

namespace xuna {

    template<typename T>
    class tree {
        using ptr_t = std::unique_ptr<tree>;

        T m_data;
        ptr_t m_left;
        ptr_t m_right;

    public:
        tree()=default;

        explicit tree(const T& value) : m_data{value} {}

        template<typename U>
        explicit tree(const U& value, const tree<T>& left) :
                m_data{value},
                m_left{std::make_unique<tree>(left)},
                m_right{nullptr} {}

        template<typename U>
        explicit tree(const U& value, const tree<T>& left, const tree<T>& right) :
                m_data{value},
                m_left{std::make_unique<tree>(left)},
                m_right{std::make_unique<tree>(right)} {}

        template<typename U, typename = std::enable_if_t<!std::is_same_v<std::decay_t<U>, tree<T>>>>
        explicit tree(U &&value): m_data{std::forward<U>(value)}{}

        template<typename U, typename V>
        explicit tree(U &&value, V &&left): m_data{std::forward<U>(value)},
            m_left{std::make_unique<tree>(std::forward<V>(left))},
            m_right{nullptr}{}

        template<typename U, typename V>
        explicit tree(U &&value, V &&left, V &&right): m_data{std::forward<U>(value)},
            m_left{std::make_unique<tree>(std::forward<V>(left))},
            m_right{std::make_unique<tree>(std::forward<V>(right))}{}
        tree(tree && t) noexcept = default;
        tree(const tree& t) noexcept : m_data{t.m_data},
            m_left{t.m_left ? std::make_unique<tree>(*t.m_left) : nullptr},
            m_right{t.m_right ? std::make_unique<tree>(*t.m_right) : nullptr} {}



        std::optional<std::reference_wrapper<tree<T>>> left(){
            return m_left != nullptr ? std::optional(std::reference_wrapper(*m_left)) : std::nullopt;
        }
        std::optional<std::reference_wrapper<tree<T>>> right(){
            return m_right != nullptr ? std::optional(std::reference_wrapper(*m_right)) : std::nullopt;
        }
        const T &value()const{
            return m_data;
        }
    };

    template<typename T, typename F>
    void bfs(tree<T> t, F f){
        f(t.value());
        if(t.left())
            bfs(t.left()->get(), f);
        if(t.right())
            bfs(t.right()->get(), f);
    }
    template<typename T, typename F>
    void dfs(tree<T> t, F f){
        if(t.left())
            bfs(t.left()->get(), f);
        f(t.value());
        if(t.right())
            bfs(t.right()->get(), f);
    }

} // xuna


