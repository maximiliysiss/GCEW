using System;
using System.Collections.Generic;
using System.Text;

namespace CommonLibrary.Utilities
{
    /// <summary>
    /// Класс для создания фабрик
    /// </summary>
    /// <typeparam name="T">Что возвращать</typeparam>
    /// <typeparam name="A">Входной аргумент</typeparam>
    /// <typeparam name="W">Условие выбора</typeparam>
    public class FactoryGenerator<T, A, W> where T : class
    {
        /// <summary>
        /// Case для выбора результата фабрики
        /// </summary>
        public class FactoryPosition
        {
            /// <summary>
            /// Генерация результата
            /// </summary>
            private readonly Func<A, T> result;
            /// <summary>
            /// Результат
            /// </summary>
            public T Result => result(default(A));
            /// <summary>
            /// Результат с аргументами
            /// </summary>
            /// <param name="arg"></param>
            /// <returns></returns>
            public T ResultWithArguments(A arg) => result(arg);
            /// <summary>
            /// Условие выбора
            /// </summary>
            private Func<W, bool> where;
            /// <summary>
            /// Установка условия выбора
            /// </summary>
            /// <param name="where"></param>
            public void Where(Func<W, bool> where) => this.where = where;
            /// <summary>
            /// Установка условия выбора
            /// </summary>
            /// <param name="where"></param>
            public void Where(W where) => this.where = (x) => where.Equals(x);
            /// <summary>
            /// Проверка условия
            /// </summary>
            /// <param name="args"></param>
            /// <returns></returns>
            public bool If(W args) => where(args);
            /// <summary>
            /// Конструктор
            /// </summary>
            /// <param name="elem"></param>
            public FactoryPosition(Func<T> elem)
            {
                this.result = (x) => elem();
            }
            /// <summary>
            /// Конструктор
            /// </summary>
            /// <param name="elem"></param>
            public FactoryPosition(Func<A, T> elem)
            {
                this.result = elem;
            }
        }

        /// <summary>
        /// Набор caseов
        /// </summary>
        protected List<FactoryPosition> factoryPositions = new List<FactoryPosition>();

        /// <summary>
        /// Добавить новую проверку
        /// </summary>
        /// <param name="elem"></param>
        /// <returns></returns>
        public FactoryPosition AddFor(Func<T> elem)
        {
            var newPos = new FactoryPosition(elem);
            factoryPositions.Add(newPos);
            return newPos;
        }

        /// <summary>
        /// Добавить новую проверку
        /// </summary>
        /// <param name="elem"></param>
        /// <returns></returns>
        public FactoryPosition AddFor(Func<A, T> elem)
        {
            var newPos = new FactoryPosition(elem);
            factoryPositions.Add(newPos);
            return newPos;
        }

        /// <summary>
        /// Построить объект
        /// </summary>
        /// <param name="where"></param>
        /// <returns></returns>
        public T Build(W where)
        {
            foreach (var elem in factoryPositions)
                if (elem.If(where))
                    return elem.Result;
            return null;
        }

        /// <summary>
        /// Построить объект с аргументами
        /// </summary>
        /// <param name="args"></param>
        /// <param name="where"></param>
        /// <returns></returns>
        public T BuildWithArguments(A args, W where)
        {
            foreach (var elem in factoryPositions)
                if (elem.If(where))
                    return elem.ResultWithArguments(args);
            return null;
        }
    }
}
