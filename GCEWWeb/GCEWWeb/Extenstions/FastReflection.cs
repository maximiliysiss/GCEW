using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Reflection;
using System.Threading.Tasks;

namespace GCEWWeb.Extenstions
{
    public class FieldValue
    {
        public string Name { get; set; }
        public object Value { get; set; }
    }


    public class FastReflection<T>
    {
        private Func<T, object> getDelegate;
        private Action<T, object> setDelegate;

        private FastReflection(PropertyInfo property)
        {
            Property = property;
            CanRead = property.GetGetMethod() != null;
            CanWrite = property.GetSetMethod() != null;
            getDelegate = t =>
            {
                InitializeGet();
                return getDelegate(t);
            };
            setDelegate = (t, p) =>
            {
                InitializeSet();
                setDelegate(t, p);
            };
        }

        public bool CanRead { get; private set; }
        public bool CanWrite { get; private set; }
        public PropertyInfo Property { get; private set; }

        public object Get(T instance)
        {
            return getDelegate(instance);
        }

        private void InitializeGet()
        {
            var getMethod = Property.GetGetMethod();
            if (getMethod != null)
            {
                var instance = Expression.Parameter(typeof(T), "instance");
                getDelegate =
                    Expression.Lambda<Func<T, object>>(Expression.TypeAs(Expression.Call(instance, getMethod), typeof(object)),
                                                       instance).Compile();
            }
        }

        private void InitializeSet()
        {
            var setMethod = Property.GetSetMethod();
            if (setMethod != null)
            {
                var instance = Expression.Parameter(typeof(T), "instance");
                var value = Expression.Parameter(typeof(object), "value");
                var valueCast = (!Property.PropertyType.IsValueType)
                                    ? Expression.TypeAs(value, Property.PropertyType)
                                    : Expression.Convert(value, Property.PropertyType);
                setDelegate =
                    Expression.Lambda<Action<T, object>>(Expression.Call(instance, setMethod, valueCast),
                                                         new[] { instance, value }).Compile();
            }
        }

        private static readonly ConcurrentDictionary<string, FastReflection<T>> properties = new ConcurrentDictionary<string, FastReflection<T>>();

        public static void SetValue(T instance, FieldValue value)
        {
            if (properties.TryGetValue(value.Name, out var prop))
                prop.Set(instance, value.Value);
            else
            {
                var newProp = new FastReflection<T>(instance.GetType().GetProperty(value.Name));
                newProp.Set(instance, value.Value);
                properties.TryAdd(value.Name, newProp);
            }
        }

        public static object GetValue(T instance, string value)
        {
            if (properties.TryGetValue(value, out var prop))
                return prop.Get(instance);
            else
            {
                var newProp = new FastReflection<T>(instance.GetType().GetProperty(value));
                properties.TryAdd(value, newProp);
                return newProp.Get(instance);
            }
        }

        public void Set(T instance, object value)
        {
            var resultValue = Convert.ChangeType(value, Property.PropertyType);
            setDelegate(instance, resultValue);
        }
    }
}
