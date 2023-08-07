#ifndef JSON_DESERIALISER_H
#define JSON_DESERIALISER_H

#include <cstddef>
#include <functional>
#include <list>
#include <map>
#include <optional>
#include <set>
#include <type_traits>
#include <variant>
#include <vector>
#include <QFile>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>

namespace JsonDeserialise {
	template<typename T>
	struct StringConvertor {
		static constexpr bool value = false;
	};

	template<>
	struct StringConvertor<char*> {
		static constexpr bool value = true;
		static inline char* convert(const QString& str) {
			const auto& src = str.toUtf8();
			char* des = new char[src.length() + 1];
			strncpy(des, src.constData(), src.length());
			des[src.length()] = '\0';
			return des;
		}

		static inline QString deconvert(char* const& src) {
			return src;
		}
	};

	template<>
	struct StringConvertor<wchar_t*> {
		static constexpr bool value = true;
		static inline wchar_t* const& convert(const QString& str) {
			wchar_t* des = new wchar_t[str.length() + 1];
			str.toWCharArray(des);
			return des;
		}

		static inline QString deconvert(wchar_t* const& src) {
			return QString::fromWCharArray(src);
		}
	};

	template<>
	struct StringConvertor<QString> {
		static constexpr bool value = true;
		static inline const QString& convert(const QString& str) {
			return str;
		}

		static inline QString deconvert(const QString& src) {
			return src;
		}
	};

	template<>
	struct StringConvertor<std::string> {
		static constexpr bool value = true;
		static inline std::string convert(const QString& str) {
			return str.toStdString();
		}

		static inline QString deconvert(const std::string& src) {
			return QString::fromStdString(src);
		}
	};

	template<>
	struct StringConvertor<QByteArray> {
		static constexpr bool value = true;
		static inline QByteArray convert(const QString& str) {
			return str.toUtf8();
		}

		static inline QString deconvert(const QByteArray& src) {
			return QString::fromUtf8(src);
		}
	};

	template<typename T>
	struct is_string {
		static constexpr bool value = StringConvertor<std::decay_t<T>>::value;
	};

	template<typename T, typename Nullable = std::optional<T>>
	struct NullableHandler {
		static constexpr bool value = false;
		inline static decltype(auto) convert(const T& value) {
			return value;
		}
		constexpr inline static decltype(auto) make_empty() {
			return std::nullopt;
		}
	};

	template<typename T>
	struct NullableHandler<T, T*> {
		static constexpr bool value = true;
		inline static T* convert(const T& value) {
			return new T(value);
		}
		constexpr inline static T* make_empty() {
			return nullptr;
		}
	};

	template<typename T>
	struct is_nullable {
		using Type = void;
		static constexpr bool value = false;
	};

	template<typename T>
	struct is_nullable<T*> {
		using Type = T;
		static constexpr bool value = true;
	};

    template<>
    struct is_nullable<char*> {
        using Type = void;
        static constexpr bool value = false;
    };

    template<>
    struct is_nullable<wchar_t*> {
        using Type = void;
        static constexpr bool value = false;
    };

    template<>
    struct is_nullable<const char*> {
        using Type = void;
        static constexpr bool value = false;
    };

    template<>
    struct is_nullable<const wchar_t*> {
        using Type = void;
        static constexpr bool value = false;
    };

	template<typename T>
	struct is_nullable<std::optional<T>> {
		using Type = T;
		static constexpr bool value = true;
	};

	class DeserialisableBase {
	public:
		const bool anonymous = false;
		const QString identifier;
		const enum class AsType : unsigned {
			NonTrivial = 0, LIMITED = 1, NULLABLE = 2, STRING = 4, INTEGER = 8, BOOLEAN = 16, DOUBLE = 32, OBJECT = 64, ARRAY_LIKE = 128
		} as;
	protected:
		DeserialisableBase(AsType _as) : anonymous(true), as(_as) {}
		DeserialisableBase(const QString& name, AsType _as) : identifier(name), as(_as) {}
		DeserialisableBase(const DeserialisableBase&) = delete;
		DeserialisableBase& operator=(const DeserialisableBase&) = delete;
	public:
		virtual ~DeserialisableBase() {}
		virtual void assign(const QJsonValue& value) = 0;
		virtual QJsonValue to_json() const = 0;
		void append(QJsonObject& parent) const {
			if (anonymous)
				throw std::ios_base::failure("JSON Structure Invalid!");
			parent.insert(identifier, to_json());
		}
		void append(QJsonArray& parent) const {
			if (!anonymous)
				throw std::ios_base::failure("JSON Structure Invalid!");
			parent.append(to_json());
		}
	};

	template<typename T = void, typename...Args>
	constexpr bool isValid() {
		return std::is_same_v<T, void> ? true : std::is_base_of_v<DeserialisableBase, T>&& isValid<Args...>();
	}

	template<class...Args>
class JsonSerialiser {
protected:
    DeserialisableBase* value[sizeof...(Args)];
    const std::enable_if_t<isValid<Args...>(), bool> is_array;

    bool isArray() {
        using AsType = DeserialisableBase::AsType;
        if (sizeof...(Args) == 1)
            return AsType(unsigned(value[0]->as) & unsigned(AsType::ARRAY_LIKE)) == AsType::ARRAY_LIKE && value[0]->anonymous;
        return false;
    }

    JsonSerialiser(Args*...args) : value{ args... }, is_array(isArray()) {}
public:
    JsonSerialiser(const Args&...args) : value{ &const_cast<Args&>(args)... }, is_array(isArray()) {}
    virtual ~JsonSerialiser() {}

    void serialise(QString filepath) const {
        QFile file(filepath);
        if (!file.open(QFile::WriteOnly))
            throw std::ios_base::failure("Failed to Open File!");
        file.write(serialise());
        file.close();
    }
    QByteArray serialise(bool compress = false) const {
        if (is_array)
            return serialise_array(compress);
        QJsonDocument json;
        QJsonObject obj;
        for (auto i : value)
            i->append(obj);
        json.setObject(obj);
        return json.toJson(QJsonDocument::JsonFormat(compress));
    }
    QByteArray serialise_array(bool compress = false) const {
        QJsonDocument json;
        QJsonArray array;
        for (auto i : value)
            i->append(array);
        json.setArray(array);
        return json.toJson(QJsonDocument::JsonFormat(compress));
    }
    QJsonValue serialise_to_json() const {
        if (is_array) {
            QJsonArray json;
            for (auto i : value)
                i->append(json);
            return json;
        }
        QJsonObject json;
        for (auto i : value)
            i->append(json);
        return json;
    }
    void serialise_to_file(QString filepath) const {
        const auto data = serialise();
        QFile file(filepath);
        if (!file.open(QFile::WriteOnly))
            throw std::ios_base::failure("Failed to Open File!");
        file.write(data);
        file.close();
    }
};

template<class...Args>
class JsonDeserialiser : public JsonSerialiser<Args...> {
    using Base = JsonSerialiser<Args...>;
    mutable bool delete_after_used = false;
public:
    JsonDeserialiser(Args*...args) : Base{ args... } {}
    JsonDeserialiser(Args&...args) : Base{ &args... } {}
    virtual ~JsonDeserialiser() {
        if (delete_after_used)
            for (auto i : Base::value)
                delete i;
    }

    void clear() const {
        delete_after_used = true;
    }
    void deserialiseFile(QString filepath) {
        QFile file(filepath);
        if (!file.open(QFile::ReadOnly))
            throw std::ios_base::failure("Failed to Open File!");
        QJsonParseError parser;
        QJsonDocument data = QJsonDocument::fromJson(file.readAll(), &parser);
        if (parser.error != QJsonParseError::NoError)
            throw std::ios_base::failure("JSON Parsing Failed!");
        if (data.isNull() || data.isEmpty())
            return;
        if (data.isArray()) {
            auto json_array = data.array();
            deserialise_array(json_array);
        }
        else {
            auto json_object = data.object();
            deserialise(json_object);
        }
        file.close();
    }
    void deserialise(const QByteArray& json) {
        QJsonParseError parser;
        QJsonDocument data = QJsonDocument::fromJson(json, &parser);
        if (parser.error != QJsonParseError::NoError)
            throw std::ios_base::failure("JSON Parsing Failed!");
        if (data.isNull() || data.isEmpty())
            return;
        if (Base::is_array) {
            if (data.isArray())
                return deserialise_array(data.array());
            else
                throw std::ios_base::failure("JSON Parsing Failed!");
        }
        auto json_object = data.object();
        deserialise(json_object);
    }
    void deserialise(const QJsonObject& object) {
        constexpr int size = sizeof...(Args);
        int count = 0;
        for (auto i : Base::value) {
            count++;
            if (i->anonymous) {
                i->assign(object);
                break;
            }
            else
                if (object.contains(i->identifier))
                    i->assign(object[i->identifier]);
        }
        if (count != size)
            throw std::ios_base::failure("JSON Structure Incompatible!");
    }
    void deserialise_array(const QJsonArray& json) {
        constexpr int size = sizeof...(Args);
        if ((unsigned(Base::value[0]->as) & unsigned(DeserialisableBase::AsType::ARRAY_LIKE)) == unsigned(DeserialisableBase::AsType::ARRAY_LIKE) && size == 1) {
            Base::value[0]->assign(json);
            return;
        }
        for (auto i : Base::value)
            if (!i->anonymous)
                throw std::ios_base::failure("JSON Parsing Failed!");
        int count = 0;
        for (const auto& i : json)
            Base::value[count++]->assign(i);
    }
};

	class Boolean : public DeserialisableBase {
        using Target = bool;
		bool& value;
	public:
		Boolean(bool& source) : DeserialisableBase(AsType::BOOLEAN), value(source) {}
		Boolean(const QString& name, bool& source) : DeserialisableBase(name, AsType::BOOLEAN), value(source) {}
		virtual void assign(const QJsonValue& data) override {
			if (data.isString()) {
				auto str = data.toString().toLower();
				if (str == "true")
					value = true;
				else if (str == "false")
					value = false;
				else if (str.isEmpty())
					value = false;
				throw std::ios_base::failure("Type Unmatch!");
			}
			else if (data.isNull())
				value = false;
			else if (data.isBool())
				value = data.toBool();
			else
				throw std::ios_base::failure("Type Unmatch!");
		}
		virtual QJsonValue to_json() const override {
			return value;
		}
	};

	template<typename T = int, bool sign = true, size_t size = 4>
	class Integer;

    template<typename T>
    class Integer<T, true, 4> : public DeserialisableBase {
        using Target = int;
        int& value;
    public:
        Integer(int& source) : DeserialisableBase(AsType::INTEGER), value(source) {}
        Integer(const QString& name, int& source) : DeserialisableBase(name, AsType::INTEGER), value(source) {}
        virtual void assign(const QJsonValue& data) override {
            if (data.isString())
                value = data.toString().toInt();
            else if (data.isDouble())
                value = data.toInt();
            else
                throw std::ios_base::failure("Type Unmatch!");
        }
        virtual QJsonValue to_json() const override {
            return value;
        }
    };

    template<typename T>
    class Integer<T, false, 4> : public DeserialisableBase {
        using Target = unsigned;
        unsigned& value;
    public:
        Integer(unsigned& source) : DeserialisableBase(AsType::INTEGER), value(source) {}
        Integer(const QString& name, unsigned& source) : DeserialisableBase(name, AsType::INTEGER), value(source) {}
        virtual void assign(const QJsonValue& data) override {
            if (data.isString())
                value = data.toString().toUInt();
            else if (data.isDouble())
                value = data.toVariant().toUInt();
            else
                throw std::ios_base::failure("Type Unmatch!");
        }
        virtual QJsonValue to_json() const override {
            return (qint64)value;
        }
    };

	template<typename T = double, size_t size = 4>
	class Real;

    template<typename T>
    class Real<T, 4> : public DeserialisableBase {
        using Target = double;
        double& value;
    public:
        Real(double& source) : DeserialisableBase(AsType::INTEGER), value(source) {}
        Real(const QString& name, double& source) : DeserialisableBase(name, AsType::INTEGER), value(source) {}
        virtual void assign(const QJsonValue& data) override {
            if (data.isString())
                value = data.toString().toDouble();
            else if (data.isDouble())
                value = data.toDouble();
            else
                throw std::ios_base::failure("Type Unmatch!");
        }
        virtual QJsonValue to_json() const override {
            return value;
        }
    };

    template<typename T, size_t length = (unsigned long long)-1>
    class String: public DeserialisableBase {
        using Target = std::decay_t<T>;
        Target& value;
    public:
        String(Target& source) : DeserialisableBase(AsType::STRING), value(source) {}
        String(const QString& name, Target& source) : DeserialisableBase(name, AsType::STRING), value(source) {}
        virtual void assign(const QJsonValue& data) override {
            if (!data.isString() && !data.isNull())
                throw std::ios_base::failure("Type Unmatch!");
            value = StringConvertor<Target>::convert(data.toString());
        }
        virtual QJsonValue to_json() const override {
            return StringConvertor<Target>::deconvert(value);
        }
    };

    template<size_t length>
    class String<char[length], length> : public DeserialisableBase {
        using Target = char[length];
        Target& value;
    public:
        String(Target& source) : DeserialisableBase(AsType::STRING), value(source) {}
        String(const QString& name, Target& source) : DeserialisableBase(name, AsType::STRING), value(source) {}
        virtual void assign(const QJsonValue& data) override {
            if (!data.isString() && !data.isNull())
                throw std::ios_base::failure("Type Unmatch!");
            auto str = data.toString().toUtf8();
            const char* c_str = str.constData();
            size_t size = length < data.toString().length() ? length : data.toString().length();
                strncpy(value, c_str, size);
            value[size] = '\0';
        }
        virtual QJsonValue to_json() const override {
            return StringConvertor<Target>::deconvert(value);
        }
    };

    template<size_t length>
    class String<char[length], 1> : public String<char*> {
        String(char source[length]) : String<char*>(source) {}
        String(const QString& name, char source[length]) : String<char*>(name, source) {}
    };

    template<typename T, typename StringType>
    class NullableString : public DeserialisableBase {
        using Target = std::decay_t<T>;
        Target& value;
    public:
        constexpr static AsType as = AsType(unsigned(AsType::STRING) & unsigned(AsType::NULLABLE));
        NullableString(Target& source) : DeserialisableBase(as), value(source) {}
        NullableString(const QString& name, Target& source) : DeserialisableBase(name, as), value(source) {}
        virtual void assign(const QJsonValue& data) override {
            if (!data.isString() && !data.isNull())
                throw std::ios_base::failure("Type Unmatch!");
            if (!data.isNull()) {
                if constexpr(NullableHandler<StringType, T>::value)
                    value = NullableHandler<StringType, T>::convert(StringConvertor<StringType>::convert(data.toString()));
                else
                    value = StringConvertor<StringType>::convert(data.toString());
            }
        }
        virtual QJsonValue to_json() const override {
            return value ? StringConvertor<StringType>::deconvert(*value) : QJsonValue();
        }
    };

	enum class ArrayPushBackWay {
		Unknown = 0,
		Push_Back = 1,
		Append = 2,
		Insert = 3
	};

	template<typename T, typename Element>
	struct choose_pushback {
		template<typename U, typename V>
		static constexpr ArrayPushBackWay calculate() {
			if (is_pushback<U, V>(nullptr))
				return ArrayPushBackWay::Push_Back;
			else if (is_append<U, V>(nullptr))
				return ArrayPushBackWay::Append;
			else if (is_insert<U, V>(nullptr))
				return ArrayPushBackWay::Insert;
			return ArrayPushBackWay::Unknown;
		}
		template<typename U, typename V, typename = decltype(std::declval<U>().push_back(std::declval<V>()))>
		static constexpr bool is_pushback(int* p) {
			return true;
		}
		template<typename...>
		static constexpr bool is_pushback(...) {
			return false;
		}
		template<typename U, typename V, typename = decltype(std::declval<U>().append(std::declval<V>()))>
		static constexpr bool is_append(int* p) {
			return true;
		}
		template<typename...>
		static constexpr bool is_append(...) {
			return false;
		}
		template<typename U, typename V, typename = decltype(std::declval<U>().insert(std::declval<V>()))>
		static constexpr bool is_insert(int* p) {
			return true;
		}
		template<typename...>
		static constexpr bool is_insert(...) {
			return false;
		}
		static constexpr ArrayPushBackWay value = calculate<T, Element>();
	};

    template<typename T, typename StringType>
    class StringArray : public DeserialisableBase {
        using Target = std::decay_t<T>;
        Target& value;
    public:
        constexpr static AsType as = AsType(unsigned(AsType::STRING) | unsigned(AsType::ARRAY_LIKE));
        StringArray(Target& source) : DeserialisableBase(as), value(source) {}
        StringArray(const QString& name, Target& source) : DeserialisableBase(name, as), value(source) {}

        virtual std::enable_if_t<bool(choose_pushback<T, StringType>::value)> assign(const QJsonValue& data) override {
            if (!data.isArray() && !data.isNull())
                throw std::ios_base::failure("Type Unmatch!");
            for (const auto& i : data.toArray())
                if constexpr (choose_pushback<T, StringType>::value == ArrayPushBackWay::Push_Back)
                    value.push_back(StringConvertor<StringType>::convert(i.toString()));
                else if constexpr (choose_pushback<T, StringType>::value == ArrayPushBackWay::Append)
                    value.append(StringConvertor<StringType>::convert(i.toString()));
                else if constexpr (choose_pushback<T, StringType>::value == ArrayPushBackWay::Insert)
                    value.insert(StringConvertor<StringType>::convert(i.toString()));
        }
        virtual QJsonValue to_json() const override {
            QJsonArray array;
            for (const auto& i : value)
                array.append(StringConvertor<StringType>::deconvert(i));
            return array;
        }
    };

    template<typename T, typename NullableStringType, typename StringType>
    class NullableStringArray : public DeserialisableBase {
        using Target = std::decay_t<T>;
        Target& value;
    public:
        constexpr static AsType as = AsType(unsigned(AsType::NULLABLE) | unsigned(AsType::STRING) | unsigned(AsType::ARRAY_LIKE));
        NullableStringArray(Target& source) : DeserialisableBase(as), value(source) {}
        NullableStringArray(const QString& name, Target& source) : DeserialisableBase(name, as), value(source) {}
        virtual void assign(const QJsonValue& data) override {
            if (!data.isArray() && !data.isNull())
                throw std::ios_base::failure("Type Unmatch!");
            for (const auto& i : data.toArray())
                if (!i.isNull())
                    value.push_back(NullableHandler<NullableStringType, StringType>::convert(StringConvertor<StringType>::convert(i.toString())));
                else
                    value.push_back(NullableHandler<NullableStringType, StringType>::make_empty());
        }
        virtual QJsonValue to_json() const override {
            QJsonArray array;
            for (const auto& i : value)
                if (i)
                    array.append(StringConvertor<StringType>::deconvert(*i));
            return array;
        }
    };

    template<typename T, typename StringType, int N>
    class LimitedStringArray : public DeserialisableBase {
        using Target = std::decay_t<T>;
        Target& value;
    public:
        constexpr static AsType as = AsType(unsigned(AsType::STRING) | unsigned(AsType::ARRAY_LIKE) | unsigned(AsType::LIMITED));
        LimitedStringArray(Target& source) : DeserialisableBase(as), value(source) {}
        LimitedStringArray(const QString& name, Target& source) : DeserialisableBase(name, as), value(source) {}
        virtual void assign(const QJsonValue& data) override {
            if (!data.isArray() && !data.isNull())
                throw std::ios_base::failure("Type Unmatch!");
            int count = 0;
            for (const auto& i : data.toArray()) {
                if (count > N - 1)
                    throw std::ios_base::failure("Array Out of Range!");
                value[count++] = StringConvertor<StringType>::convert(i.toString());
            }
        }
        virtual QJsonValue to_json() const override {
            QJsonArray array;
            for (const auto& i : value) {
                QString str = StringConvertor<StringType>::deconvert(i);
                if (!str.isEmpty())
                    array.append(str);
            }
            return array;
        }
    };

    template<typename T, typename NullableStringType, typename StringType, int N>
    class LimitedNullableStringArray : public DeserialisableBase {
        using Target = std::decay_t<T>;
        Target& value;
    public:
        constexpr static AsType as = AsType(unsigned(AsType::NULLABLE) | unsigned(AsType::STRING) | unsigned(AsType::ARRAY_LIKE) | unsigned(AsType::LIMITED));
        LimitedNullableStringArray(Target& source) : DeserialisableBase(as), value(source) {}
        LimitedNullableStringArray(const QString& name, Target& source) : DeserialisableBase(name, as), value(source) {}
        virtual void assign(const QJsonValue& data) override {
            if (!data.isArray() && !data.isNull())
                throw std::ios_base::failure("Type Unmatch!");
            int count = 0;
            for (const auto& i : data.toArray()) {
                if (count > N - 1)
                    throw std::ios_base::failure("Array Out of Range!");
                if (!i.isNull())
                    value[count++] = NullableHandler<NullableStringType, StringType>::convert(StringConvertor<StringType>::convert(i.toString()));
                else
                    value[count++] = NullableHandler<NullableStringType, StringType>::make_empty();
            }
        }
        virtual QJsonValue to_json() const {
            QJsonArray array;
            for (const auto& i : value) {
                if (i && !i->isEmpty())
                    array.append(*i);
            }
            return array;
        }
    };

	//Primary Template
	template <typename Any, bool isArray = false, int size = -1, typename TypeInArray = void, int isNullable = -1, typename TypeInNullable = void, int isString = -1>
	struct _Deserialisable;

	template<typename Any, bool isArray = false, int size = -1, typename TypeInArray = void, int isNullable = -1, typename TypeInNullable = void, int isString = -1>
	using _DeserialisableType = typename _Deserialisable<std::decay_t<Any>, isArray, size, TypeInArray, isNullable, TypeInNullable, isString>::Type;

	template<typename Any>
	struct Deserialisable {
		using Type = _DeserialisableType<Any>;
	};

	template<typename Any>
	using DeserialisableType = typename Deserialisable<std::decay_t<Any>>::Type;

	template<class T, typename...WrappedMembers>
	class Object : public DeserialisableBase {
        using Type = T;
		JsonDeserialiser<WrappedMembers...> deserialiser;
	public:
		constexpr static AsType as = AsType::OBJECT;
		Object(T* _, WrappedMembers&...members) : DeserialisableBase(as), deserialiser(&members...) {}
		Object(T* _, WrappedMembers*...members) : DeserialisableBase(as), deserialiser(members...) {}
		Object(const QString& name, T* _, WrappedMembers&...members) : DeserialisableBase(name, as), deserialiser(&members...) {}
		Object(const QString& name, T* _, WrappedMembers*...members) : DeserialisableBase(name, as), deserialiser(members...) {}

		virtual void assign(const QJsonValue& data) override {
			if (!data.isObject() && !data.isNull())
				throw std::ios_base::failure("Type Unmatch!");
			if (!data.isNull())
				deserialiser.deserialise(data.toObject());
		}
		virtual QJsonValue to_json() const override {
			return deserialiser.serialise_to_json();
		}
		inline void clear() const {
			deserialiser.clear();
		}
	};

	template<typename T>
	struct Info {
		const char* name;
		T* ptr;
		Info(const char* id, T* p) : name(id), ptr(p) {}
	};

	template<typename T, class ObjectType, typename...Members>
	class ObjectArray : public DeserialisableBase {
        using Target = T;
		using Prototype = Object<ObjectType, DeserialisableType<Members>...>;
		T& value;
		static constexpr size_t size = sizeof...(Members);
		size_t offset[size];
		const char* names[size];
	public:
		constexpr static AsType as = AsType(unsigned(AsType::ARRAY_LIKE) | unsigned(AsType::OBJECT));
		ObjectArray(T& source, ObjectType* object_ptr, Info<Members>&&...members) : DeserialisableBase(as), value(source), offset{ reinterpret_cast<size_t>(members.ptr)... }, names{ members.name... } {}
		ObjectArray(const QString& name, T& source, ObjectType* object_ptr, Info<Members>&&...members) : DeserialisableBase(name, as), value(source), offset{ reinterpret_cast<size_t>(members.ptr)... }, names{ members.name... } {}

		virtual std::enable_if_t<bool(choose_pushback<T, ObjectType>::value)> assign(const QJsonValue& data) override {
			if (!data.isArray() && !data.isNull())
				throw std::ios_base::failure("Type Unmatch!");
			for (const auto& i : data.toArray()) {
				if constexpr (choose_pushback<T, ObjectType>::value == ArrayPushBackWay::Push_Back)
					value.push_back(ObjectType());
				else if constexpr (choose_pushback<T, ObjectType>::value == ArrayPushBackWay::Append)
					value.append(ObjectType());
				else if constexpr (choose_pushback<T, ObjectType>::value == ArrayPushBackWay::Insert)
					value.insert(ObjectType());
				auto ptr = &value.back();
				int nameCount = size, dataCount = size;
				Prototype deserialiser((ObjectType*)nullptr, new DeserialisableType<Members>(names[--nameCount], *reinterpret_cast<Members*>(reinterpret_cast<uint8_t*>(ptr) + offset[--dataCount]))...);
				deserialiser.assign(i);
				deserialiser.clear();
			}
		}
		virtual QJsonValue to_json() const override {
			QJsonArray array;
			for (const auto& i : value) {
				const auto ptr = &i;
				int nameCount = size, dataCount = size;
				const Prototype serialiser((ObjectType*)nullptr, new DeserialisableType<Members>(names[--nameCount], const_cast<Members&>(*reinterpret_cast<const Members*>(reinterpret_cast<const uint8_t*>(ptr) + offset[--dataCount])))...);
				array.append(serialiser.to_json());
				serialiser.clear();
			}
			return array;
		}
	};

	template<typename T, typename TrivialType>
	class Array : public DeserialisableBase {
        using Target = std::decay_t<T>;
        using Prototype = DeserialisableType<TrivialType>;
        Target& value;
    public:
        Array(Target& source) : DeserialisableBase(AsType::ARRAY_LIKE), value(source) {}
        Array(const QString& name, Target& source) : DeserialisableBase(name, AsType::ARRAY_LIKE), value(source) {}

		virtual std::enable_if_t<bool(choose_pushback<T, TrivialType>::value)> assign(const QJsonValue& data) override {
			if (!data.isArray() && !data.isNull())
				throw std::ios_base::failure("Type Unmatch!");
			for (const auto& i : data.toArray()) {
				if constexpr (choose_pushback<T, TrivialType>::value == ArrayPushBackWay::Push_Back)
					value.push_back(TrivialType());
				else if constexpr (choose_pushback<T, TrivialType>::value == ArrayPushBackWay::Append)
					value.append(TrivialType());
				else if constexpr (choose_pushback<T, TrivialType>::value == ArrayPushBackWay::Insert)
					value.insert(TrivialType());
				Prototype deserialiser(value.back());
				deserialiser.assign(i);
			}
		}
		virtual QJsonValue to_json() const override {
			QJsonArray array;
			for (const auto& i : value) {
				const Prototype deserialiser(const_cast<TrivialType&>(i));
				array.append(deserialiser.to_json());
			}
			return array;
		}
	};

    template<typename T, typename TypeInNullable>
    class Nullable : public DeserialisableBase {
        using Target = std::decay_t<T>;
        Target& value;
    public:
        Nullable(Target& source) : DeserialisableBase(AsType::NULLABLE), value(source) {}
        Nullable(const QString& name, T& source) : DeserialisableBase(name, AsType::NULLABLE), value(source) {}
        virtual void assign(const QJsonValue& data) override {
            if (data.isNull()) {
                value = NullableHandler<TypeInNullable, Target>::make_empty();
                return;
            }
            TypeInNullable tmp;
            DeserialisableType<TypeInNullable> serialiser(tmp);
            serialiser.assign(data);
            value = NullableHandler<TypeInNullable, Target>::convert(tmp);
        }
        virtual QJsonValue to_json() const override {
            QJsonValue result;
            if (value)
                result = DeserialisableType<TypeInNullable>(*value).to_json();
            return result;
        }
    };

    template<typename T, typename As>
    class NonTrivial : public DeserialisableBase {
        using Target = std::decay_t<T>;
        DeserialisableType<As> value;
    public:
		NonTrivial(Target& source) : DeserialisableBase(AsType::NonTrivial), value(reinterpret_cast<As&>(source)) {}
		NonTrivial(const QString& name, Target& source) : DeserialisableBase(name, AsType::NonTrivial), value(name, reinterpret_cast<As&>(source)) {}
		virtual void assign(const QJsonValue& data) override {
			value.assign(data);
		}
		virtual QJsonValue to_json() const override {
			return value.to_json();
		}
	};

	template<typename T, const char* json_name, size_t member_offset>
	struct ReinforcedInfo {
		using Type = T;
		static constexpr const char* name = json_name;
		static constexpr size_t offset = member_offset;
	};

    template<typename ObjectType, typename...MemberInfo>
    class DeserialisableObject : public DeserialisableBase {
        using Target = ObjectType;
		Object<ObjectType, DeserialisableType<typename MemberInfo::Type>...> serialiser;
	public:
		DeserialisableObject(QString json_name, ObjectType& value) : DeserialisableBase(json_name, AsType::OBJECT), serialiser(json_name, &value, new DeserialisableType<typename MemberInfo::Type>(MemberInfo::name, (typename MemberInfo::Type&)* ((uint8_t*)(&value) + MemberInfo::offset))...) {}
		DeserialisableObject(ObjectType& value) : DeserialisableBase(AsType::OBJECT), serialiser(&value, new DeserialisableType<typename MemberInfo::Type>(MemberInfo::name, (typename MemberInfo::Type&)* ((uint8_t*)(&value) + MemberInfo::offset))...) {}
		virtual void assign(const QJsonValue& data) override {
			serialiser.assign(data);
		}
		virtual QJsonValue to_json() const override {
			return serialiser.to_json();
		}
		~DeserialisableObject() {
			serialiser.clear();
		}
	};

    template<typename T>
    class SelfDeserialisableObject : public DeserialisableBase {
        using Target = std::decay_t<T>;
        Target& value;
    public:
        constexpr static AsType as = AsType::OBJECT;
        SelfDeserialisableObject(Target& source) : DeserialisableBase(as), value(source) {}
        virtual void assign(const QJsonValue& data) override {
            if (!data.isObject() && !data.isNull())
                throw std::ios_base::failure("Type Unmatch!");
            if (data.isObject())
                value = std::move(Target(data.toObject()));
        }
        virtual QJsonValue to_json() const override {
            return value.to_json();
        }
    };

    template<typename T, typename KeyType, typename ValueType, const char* KeyName = nullptr>
    class MapArray : public DeserialisableBase {
        using Target = std::decay_t<T>;
        Target& value;
        QString key = KeyName;
    public:
        MapArray(Target& source) : DeserialisableBase(AsType(unsigned(AsType(AsType::ARRAY_LIKE)) | unsigned(AsType(AsType::OBJECT)))), value(source) {}
        virtual void assign(const QJsonValue& data) override {
            if (!data.isArray() && !data.isNull())
                throw std::ios_base::failure("Type Unmatch!");
            for (const auto& i : data.toArray()) {
                KeyType key_value;
                ValueType value_value;
                DeserialisableType<KeyType> key_deserialiser(key_value);
                DeserialisableType<ValueType> value_deserialiser(value_value);
                key_deserialiser.assign(i.toObject()[key]);
                value_deserialiser.assign(i);
                value[key_value] = value_value;
            }
        }
        virtual QJsonValue to_json() const override {
            QJsonArray array;
            for (const auto& [key_, value_] : value) {
                KeyType key_value = key_;
                ValueType value_value = value_;
                DeserialisableType<KeyType> key_deserialiser(key_value);
                DeserialisableType<ValueType> value_deserialiser(value_value);
                QJsonObject obj = value_deserialiser.to_json().toObject();
                obj.insert(key, key_deserialiser.to_json());
                array.append(obj);
            }
            return array;
        }
    };

    template<typename T, typename KeyType, typename ValueType>
    class MapArray<T, KeyType, ValueType, nullptr> : public DeserialisableBase {
        using Target = std::decay_t<T>;
        Target& value;
        QString key;
        std::optional<QString> val_name;
    public:
        MapArray(Target& source, QString key_name = QStringLiteral("key")) : DeserialisableBase(AsType(unsigned(AsType::ARRAY_LIKE) | unsigned(AsType::OBJECT))), value(source), key(key_name) {}
        MapArray(Target& source, QString key_name, QString val_json_name) : DeserialisableBase(AsType(unsigned(AsType::ARRAY_LIKE) | unsigned(AsType::OBJECT))), value(source), key(key_name), val_name(val_json_name) {}

		virtual void assign(const QJsonValue& data) override {
			if (!data.isArray() && !data.isNull())
				throw std::ios_base::failure("Type Unmatch!");
			for (const auto& i : data.toArray()) {
				KeyType key_value;
				ValueType value_value;
				DeserialisableType<KeyType> key_deserialiser(key_value);
				DeserialisableType<ValueType> value_deserialiser(value_value);
				key_deserialiser.assign(i.toObject()[key]);
				if (val_name)
					value_deserialiser.assign(i.toObject()[*val_name]);
				else
					value_deserialiser.assign(i);
				value[key_value] = value_value;
			}
		}
		virtual QJsonValue to_json() const override {
			QJsonArray array;
			for (const auto& [key_, value_] : value) {
				KeyType key_value = key_;
				ValueType value_value = value_;
				DeserialisableType<KeyType> key_deserialiser(key_value);
				DeserialisableType<ValueType> value_deserialiser(value_value);
				QJsonObject obj;
				if (val_name)
					obj = value_deserialiser.to_json().toObject();
				else
					obj.insert(*val_name, value_deserialiser.to_json());
				obj.insert(key, key_deserialiser.to_json());
				array.append(obj);
			}
			return array;
		}
	};

    template<class Base, class T, typename...MemberInfo>
    class DerivedObject : public DeserialisableBase {
        using Target = T;
		Object<T, DeserialisableType<typename MemberInfo::Type>...> serialiser;
		std::enable_if_t<std::is_base_of_v<Base, T>, DeserialisableType<Base>> base_serialiser;
	public:
		DerivedObject(const QString& json_name, T& value) : DeserialisableBase(json_name, AsType::OBJECT), serialiser(json_name, &value, new DeserialisableType<typename MemberInfo::Type>(MemberInfo::name, (typename MemberInfo::Type&)* ((uint8_t*)(&value) + MemberInfo::offset))...), base_serialiser(dynamic_cast<Base&>(value)) {}
		DerivedObject(T& value) : DeserialisableBase(AsType::OBJECT), serialiser(&value, new DeserialisableType<typename MemberInfo::Type>(MemberInfo::name, (typename MemberInfo::Type&)* ((uint8_t*)(&value) + MemberInfo::offset))...), base_serialiser(dynamic_cast<Base&>(value)) {}
		virtual void assign(const QJsonValue& data) override {
			serialiser.assign(data);
			base_serialiser.assign(data);
		}
		virtual QJsonValue to_json() const override {
			QJsonObject result = serialiser.to_json().toObject();
			QJsonObject base = base_serialiser.to_json().toObject();
			for (auto i = base.begin(); i != base.end(); i++)
				result.insert(i.key(), i.value());
			return result;
		}
		~DerivedObject() {
			serialiser.clear();
		}
	};

    template<typename T, typename Type1, typename Type2>
    class Pair : public DeserialisableBase {
        using Target = std::decay_t<T>;
        Target& value;
        QString name[2];
    public:
        Pair(Target& source, const QString& name1, const QString& name2) : DeserialisableBase(AsType::OBJECT), value(source), name{ name1, name2 } {}
        Pair(const QString& json_name, Target& source, const QString& name1, const QString& name2) : DeserialisableBase(json_name, AsType::OBJECT), value(source), name{ name1, name2 } {}

		virtual void assign(const QJsonValue& data) override {
			if (!data.isObject() && !data.isNull())
				throw std::ios_base::failure("Type Unmatch!");
			for (const auto& i : data.toArray()) {
				Type1& element1 = value.first;
				Type2& element2 = value.second;
				DeserialisableType<Type1> deserialiser1(element1);
				DeserialisableType<Type2> deserialiser2(element2);
				deserialiser1.assign(i.toObject()[name[0]]);
				deserialiser2.assign(i.toObject()[name[1]]);
			}
		}
		virtual QJsonValue to_json() const override {
			QJsonObject pair;
			Type1& element1 = value.first;
			Type2& element2 = value.second;
			DeserialisableType<Type1> deserialiser1(element1);
			DeserialisableType<Type2> deserialiser2(element2);
			pair.insert(name[0], deserialiser1.to_json());
			pair.insert(name[1], deserialiser2.to_json());
			return pair;
		}
	};

    template<typename T, typename PairType>
    class PairArray : public DeserialisableBase {
        using Target = std::decay_t<T>;
        Target& value;
        QString name[2];
    public:
        PairArray(Target& source, const QString& name1, const QString& name2) : DeserialisableBase(AsType::ARRAY_LIKE), value(source), name{ name1, name2 } {}

		virtual std::enable_if_t<bool(choose_pushback<T, PairType>::value)> assign(const QJsonValue& data) override {
			if (!data.isArray() && !data.isNull())
				throw std::ios_base::failure("Type Unmatch!");
			for (const auto& i : data.toArray()) {
				if constexpr (choose_pushback<T, PairType>::value == ArrayPushBackWay::Push_Back)
					value.push_back(PairType());
				else if constexpr (choose_pushback<T, PairType>::value == ArrayPushBackWay::Append)
					value.append(PairType());
				else if constexpr (choose_pushback<T, PairType>::value == ArrayPushBackWay::Insert)
					value.insert(PairType());
				PairType& pair = value.back();
				DeserialisableType<PairType> deserialiser(pair, name[0], name[1]);
				deserialiser.assign(i);
			}
		}
		virtual QJsonValue to_json() const override {
			QJsonArray array;
			for (const auto& i : value) {
				DeserialisableType<PairType> deserialiser(i, name[0], name[1]);
				array.append(deserialiser.to_json());
			}
			return array;
		}
	};

    template<typename Des, typename ConvertFunctor = Des(const QJsonValue&), typename DeconvertFunctor = QJsonValue(const Des&), typename BasicType = decltype(std::declval<DeconvertFunctor>()(std::declval<Des>()))>
    struct Convertor {
        using Type = BasicType;
        using Target = std::decay_t<Des>;
        using Source = std::decay_t<BasicType>;
        decltype(std::function(std::declval<ConvertFunctor>())) convertor;
        decltype(std::function(std::declval<DeconvertFunctor>())) deconvertor;
        Convertor(ConvertFunctor& convertor, DeconvertFunctor& deconvertor) : convertor(convertor), deconvertor(deconvertor) {}
        explicit Convertor()
            : convertor
            {
                [](const QJsonValue& data) {
                    using T = DeserialisableType<Des>;
                    Des result;
                    T(result).assign(data);
                    return result;
                }
            },
            deconvertor
            {
                [](const Des& src) {
                    using T = DeserialisableType<Des>;
                    return T(const_cast<Des&>(src)).to_json();
                }
            }
        {}
        template<typename OtherConvertFunctor, typename otherDeconvertFunctor>
        Convertor(Convertor<Des, OtherConvertFunctor, otherDeconvertFunctor, BasicType>&& other) : convertor(std::move(other.convertor)), deconvertor(std::move(other.deconvertor)) {}
    };

    template<typename T>
    struct Remove_Const_Of_C_Style {
        static constexpr bool value = false;
        using Type = T;
    };

    template<>
    struct Remove_Const_Of_C_Style<const char*> {
        static constexpr bool value = true;
        using Type = char*;
    };

    template<>
    struct Remove_Const_Of_C_Style<const wchar_t*> {
        static constexpr bool value = true;
        using Type = wchar_t*;
    };

    template<typename Convertor>
    class Extension : public DeserialisableBase {
    public:
        using Type = DeserialisableType<typename Convertor::Type>;
        using Target = typename Convertor::Target;
    private:
        Target& value;
        mutable typename Remove_Const_Of_C_Style<typename Convertor::Source>::Type tmp;
        std::decay_t<Convertor> convertor;
        Type prototype;
    public:
        Extension(Convertor&& convertor, Target& source) : DeserialisableBase(AsType::NonTrivial), value(source), convertor(convertor), prototype(tmp) {}
        Extension(Convertor&& convertor, const QString& json_name, Target& source) : DeserialisableBase(json_name, AsType::STRING), value(source), convertor(convertor), prototype(tmp) {}

        virtual void assign(const QJsonValue& data) override {
            prototype.assign(data);
            value = convertor.convertor(tmp);
        }
        virtual QJsonValue to_json() const override {
            if constexpr(Remove_Const_Of_C_Style<typename Convertor::Source>::value)
                tmp = const_cast<typename Remove_Const_Of_C_Style<typename Convertor::Source>::Type>(convertor.deconvertor(value));
            else
                tmp = convertor.deconvertor(value);
            return prototype.to_json();
        }
    };

	template<typename Function>
	struct ArgTypeDeduction {
    	using Type = typename ArgTypeDeduction<decltype(&Function::operator())>::Type;
	};

	template<typename R, class C, typename Arg>
	struct ArgTypeDeduction<R(C::*)(Arg)const> {
    	using Type = Arg;
	};

	template<typename Des, typename ConvertFunctor , typename BasicType = std::decay_t<typename ArgTypeDeduction<decltype(std::function(std::declval<ConvertFunctor>()))>::Type>>
	struct OneDirectionConvertor {
    	using Type = BasicType;
    	using Target = std::decay_t<Des>;
    	using Source = std::decay_t<BasicType>;
    	decltype(std::function(std::declval<ConvertFunctor>())) convertor;
    	OneDirectionConvertor(ConvertFunctor& convertor) : convertor(convertor) {}
    	template<typename OtherConvertFunctor>
    	OneDirectionConvertor(OneDirectionConvertor<Des, OtherConvertFunctor, BasicType>&& other) : convertor(std::move(other.convertor)) {}
	};

	template<typename Convertor>
	class OneDirectionExtension : public DeserialisableBase {
	public:
    	using Type = DeserialisableType<typename Convertor::Type>;
    	using Target = typename Convertor::Target;
	private:
    	Target& value;
    	mutable typename Remove_Const_Of_C_Style<typename Convertor::Source>::Type tmp;
    	std::decay_t<Convertor> convertor;
    	Type prototype;
	public:
    	OneDirectionExtension(Convertor&& convertor, Target& source) : DeserialisableBase(AsType::NonTrivial), value(source), convertor(convertor), prototype(tmp) {}
    	OneDirectionExtension(Convertor&& convertor, const QString& json_name, Target& source) : DeserialisableBase(json_name, AsType::STRING), value(source), convertor(convertor), prototype(tmp) {}

    	virtual void assign(const QJsonValue& data) override {
        	prototype.assign(data);
        	value = convertor.convertor(tmp);
    	}
    	virtual QJsonValue to_json() const override {
        	throw std::ios_base::failure("Serialisation Unsupportted!");
    	}
	};

	template<int index, typename Tuple>
	struct GetType : GetType<index - 1, typename Tuple::Next> {};

	template<typename Tuple>
	struct GetType<0, Tuple> {
		using Type = typename Tuple::CurrentType;
	};

    template<typename Current = void, typename...Types>
    struct StaticTuple {
        Current value;
        using Next = StaticTuple<Types...>;
        Next next;
        using CurrentType = Current;

        StaticTuple(Current&& source, Types&&... pack) : value(std::move(source)), next(std::forward<Types>(pack)...) {}

		template<int index>
		inline typename GetType<index, StaticTuple>::Type& get() {
			if constexpr (index == 0)
				return value;
			else
				return next.template get<index - 1>();
		}

        template<int index>
        inline const typename GetType<index, StaticTuple>::Type& get() const {
            if constexpr (index == 0)
                return value;
            else
                return next.template get<index - 1>();
        }
	};

    template<typename Current>
    struct StaticTuple<Current> {
        Current value;
        using CurrentType = Current;

        StaticTuple(Current&& source) : value(std::move(source)) {}

		template<int index, typename = std::enable_if_t<index == 0>>
		inline Current& get() {
			return value;
		}

        template<int index, typename = std::enable_if_t<index == 0>>
        inline const typename GetType<index, StaticTuple>::Type& get() const {
            return value;
        }
	};

    template<>
    struct StaticTuple<void> {};

	struct FAM {
		virtual void run() = 0;
		virtual ~FAM() {}
	};

	template<typename Convertor, typename Target>
	struct Assign : public FAM {
		const QJsonValue& data;
		Convertor& convertor;
		Target& value;

        void run() override {
            value = std::move(convertor.convertor(data));
        }

		Assign(const QJsonValue& data, Convertor& convertor, Target& source) : data(data), convertor(convertor), value(source) {}
	};

    template<typename Convertor, typename Source>
    struct To_Json : public FAM {
        QJsonObject& result;
        const Convertor& convertor;
        const Source& value;

        void run() override {
            result = std::move(convertor.deconvertor(std::get<typename Convertor::Target>(value)).toObject());
        }

        To_Json(QJsonObject& data, const Convertor& convertor, const Source& source) : result(data), convertor(convertor), value(source) {}
    };

	template<int...pack>
	struct ConstexprArrayPack {
		constexpr static int length = sizeof...(pack);
		constexpr static int value[sizeof...(pack)] = { pack... };
	};

    template<>
    struct ConstexprArrayPack<> {
        constexpr static int length = 0;
    };

	template<int N, int current = 0, int...pack>
	struct ConstexprIncArray : public ConstexprIncArray<N, current + 1, pack..., current> {};

	template<int N, int...pack>
	struct ConstexprIncArray<N, N, pack...> : public ConstexprArrayPack<pack...> {
		using Type = ConstexprArrayPack<pack...>;
	};

    template<int N, int Constant, typename Result = ConstexprArrayPack<Constant>, int num = 1, bool = N == num, typename = std::enable_if_t<(N >= 0)>>
    struct ConstexprConstantArray;

    template<int N, int Constant, int...Result, int num>
    struct ConstexprConstantArray<N, Constant, ConstexprArrayPack<Result...>, num, false> {
        using Next = ConstexprConstantArray<N, Constant, ConstexprArrayPack<Constant, Result...>, num + 1>;
        using Type = typename Next::Type;
    };

    template<int N, int Constant, int...Result>
    struct ConstexprConstantArray<N, Constant, ConstexprArrayPack<Result...>, N, true> {
        using Type = ConstexprArrayPack<Result...>;
    };

    template<int Constant>
    struct ConstexprConstantArray<0, Constant, ConstexprArrayPack<Constant>, 1, false> {
        using Type = ConstexprArrayPack<>;
    };

    template<typename pack, int N, int current = 0, typename Result = ConstexprArrayPack<>, bool = N == current, typename = std::enable_if_t<(N <= pack::length)>>
    struct ConstexprArrayPackFront;

    template<typename pack, int N, int current, int...Last>
    struct ConstexprArrayPackFront<pack, N, current, ConstexprArrayPack<Last...>, false> {
        using Current = ConstexprArrayPack<Last..., pack::value[current]>;
        using Type = typename ConstexprArrayPackFront<pack, N, current + 1, Current>::Type;
    };

    template<typename pack>
    struct ConstexprArrayPackFront<pack, 0> {
        using Type = ConstexprArrayPack<>;
    };

    template<typename pack, int N, int...Last>
    struct ConstexprArrayPackFront<pack, N, N, ConstexprArrayPack<Last...>, true> {
        using Type = ConstexprArrayPack<Last...>;
    };

    template<typename pack, int N, int current = 0, typename Result = ConstexprArrayPack<>, bool = N == current, typename = std::enable_if_t<(N <= pack::length)>>
    struct ConstexprArrayPackBack;

    template<typename pack>
    struct ConstexprArrayPackBack<pack, 0> {
        using Type = ConstexprArrayPack<>;
    };

    template<typename pack, int N, int current, int...Last>
    struct ConstexprArrayPackBack<pack, N, current, ConstexprArrayPack<Last...>, false> {
        using Current = ConstexprArrayPack<pack::value[pack::length - 1 - current], Last...>;
        using Type = typename ConstexprArrayPackFront<pack, N, current + 1, Current>::Type;
    };

    template<typename pack, int N, int...Last>
    struct ConstexprArrayPackBack<pack, N, N, ConstexprArrayPack<Last...>, true> {
        using Type = ConstexprArrayPack<Last...>;
    };

    template<typename front, int middle, typename back>
    struct ConstexprArrayPackMerge;

    template<int...front, int middle, int...back>
    struct ConstexprArrayPackMerge<ConstexprArrayPack<front...>, middle, ConstexprArrayPack<back...>> {
        using Type = ConstexprArrayPack<front..., middle, back...>;
    };

    template<int loc, int Constant, typename pack, typename = std::enable_if_t<(loc >= 0 && loc < pack::length)>>
    struct ConstexprArrayPackAlter {
        using Type = typename ConstexprArrayPackMerge<typename ConstexprArrayPackFront<pack, loc>::Type, Constant, typename ConstexprArrayPackBack<pack, pack::length - 1 - loc>::Type>::Type;
    };

    template<typename Tuple, typename T, int index = 0, bool = std::is_same_v<T, typename GetType<index, Tuple>::Type>, typename = std::enable_if_t<(index < Tuple::length)>>
    struct FindType : public FindType<Tuple, T, index + 1> {};

    template<typename Tuple, typename T, int Index>
    struct FindType<Tuple, T, Index, true> {
        static constexpr int index = Index;
    };

    template<typename Current = void, typename...Types>
    struct TypeTuple {
        using Next = TypeTuple<Types...>;
        using CurrentType = Current;
        static constexpr int length = sizeof...(Types) + 1;
    };

    template<typename Current>
    struct TypeTuple<Current> {
        using CurrentType = Current;
        static constexpr int length = 1;
    };

    template<>
    struct TypeTuple<void> {
        static constexpr int length = 0;
    };

    template<typename Standard, typename Tuple, int current = 0, typename Result = typename ConstexprConstantArray<Standard::length, -1>::Type, bool = Tuple::length <= 1>
    struct ConvertorAdapterReorganise;

    template<typename...Targets, int current, typename Last, typename Current, typename...Left>
    struct ConvertorAdapterReorganise<TypeTuple<Targets...>, TypeTuple<Current, Left...>, current, Last, false> {
        static constexpr int index = FindType<TypeTuple<Targets...>, typename Current::Target>::index;
        using Next = ConvertorAdapterReorganise<TypeTuple<Targets...>, TypeTuple<Left...>, current + 1, typename ConstexprArrayPackAlter<index, current, Last>::Type>;
        using Type = typename Next::Type;
    };

    template<typename...Targets, int current, typename Last, typename Current>
    struct ConvertorAdapterReorganise<TypeTuple<Targets...>, TypeTuple<Current>, current, Last, true> {
        static constexpr int index = FindType<TypeTuple<Targets...>, typename Current::Target>::index;
        using Type = typename ConstexprArrayPackAlter<index, current, Last>::Type;
    };

    template<typename...Targets, typename Result>
    struct ConvertorAdapterReorganise<TypeTuple<Targets...>, TypeTuple<void>, 0, Result, true> {
        using Type = Result;
    };

    template<int N, typename Target, typename Given>
    inline Convertor<Target> ConvertorGenerator(Given& given) {
        if constexpr(N == -1)
            return std::move(Convertor<Target>());
        else
            return std::move(given.template get<N>());
    };

    template<typename Target, typename Inc, typename...Given>
    struct ConvertorAdapter;

    template<typename...Targets, int...pack, typename...Given>
    struct ConvertorAdapter<std::variant<Targets...>, ConstexprArrayPack<pack...>, Given...> {
        using Array = typename ConvertorAdapterReorganise<TypeTuple<Targets...>, TypeTuple<Given...>>::Type;
        using Tuple = TypeTuple<Given...>;
        using Target = TypeTuple<Targets...>;
        StaticTuple<Convertor<Given>...> givens;
        StaticTuple<Convertor<Targets>...> convertors;
        ConvertorAdapter(Given&...given) : givens(given...), convertors(ConvertorGenerator<Array::value[pack], typename GetType<pack, Target>::Type>(givens)...) {}
    };

    template<typename Variant>
    struct GetNum;

    template<typename...Types>
    struct GetNum<std::variant<Types...>> {
        constexpr static int value = sizeof...(Types);
    };

    //Deductor = Convertor<int, ConvertFunctor, DeconvertFunctor, BasicType>;
    template<typename Deductor, typename Target, typename Inc = typename ConstexprIncArray<GetNum<Target>::value>::Type>
    class VarientObject;

    template<typename Deductor, typename...Targets, int...pack>
    class VarientObject<Deductor, std::variant<Targets...>, ConstexprArrayPack<pack...>> : public DeserialisableBase {
        using Target = std::variant<Targets...>;
        mutable int result = -1;
        Extension<Deductor> deductor;
        StaticTuple<Convertor<Targets>...> convertors;
        Target& value;
    public:
        template<typename...Given_Convertors>
        VarientObject(const QString& key, Deductor&& deduction, Target& source, Given_Convertors&&... convertors)
            : DeserialisableBase(AsType::OBJECT), deductor(std::move(deduction) , key, result), convertors(ConvertorAdapter<Target, ConstexprArrayPack<pack...>, Given_Convertors...>(convertors...).convertors), value(source) {}
        template<typename...Given_Convertors>
        VarientObject(const QString& name, const QString& key, Deductor&& deduction, Target& source, Given_Convertors&&... convertors)
            : DeserialisableBase(name, AsType::OBJECT), deductor(std::move(deduction), key, result), convertors(ConvertorAdapter<Target, ConstexprArrayPack<pack...>, Given_Convertors...>(convertors...).convertors), value(source) {}

        virtual void assign(const QJsonValue& data) override {
            if (!data.isObject() || !data.toObject().contains(deductor.identifier))
                throw std::ios_base::failure("Type Unmatch!");
            deductor.assign(data.toObject()[deductor.identifier]);
            if (result == -1)
                throw std::ios_base::failure("Type Unmatch!");
            FAM* machines[sizeof...(Targets)] = { (new Assign(data, convertors.template get<pack>(), value))... };
            machines[result]->run();
            for (auto i : machines)
                delete i;
        }
        virtual QJsonValue to_json() const override {
            QJsonObject object;
            result = value.index();
            FAM* machines[sizeof...(Targets)] = { (new To_Json(object, convertors.template get<pack>(), value))... };
            machines[result]->run();
            for (auto i : machines)
                delete i;
            return object;
        }
    };

    struct JSONWrap : public DeserialisableBase {
        QJsonValue& value;
        JSONTypeWrap(QJsonValue& src) : DeserialisableBase(AsType::NonTrivial), value(src) {}
        JSONTypeWrap(const QString& name, QJsonValue& src) : DeserialisableBase(name, AsType::NonTrivial), value(src) {}

        virtual void assign(const QJsonValue& data) override {
            value = data;
        }
        virtual QJsonValue to_json() const override {
            return value;
        }
    };

	template<typename Any>
	struct _Deserialisable<Any, false, -1, void, -1, void, -1> {
		using Type = _DeserialisableType<Any, false, -1, void, is_nullable<Any>::value, typename is_nullable<Any>::Type, -1>;
	};

	template<typename Any>
	struct _Deserialisable<Any, false, -1, void, false, void, -1> {
		using Type = _DeserialisableType<Any, false, -1, void, false, void, is_string<Any>::value>;
	};

	template<typename T, typename TypeInNullable>
	struct _Deserialisable<T, false, -1, void, true, TypeInNullable, -1> {
		using Type = _DeserialisableType<T, false, -1, void, true, TypeInNullable, is_string<TypeInNullable>::value>;
	};

	template<typename T, typename TypeInArray>
	struct _Deserialisable<T, true, -1, TypeInArray, -1, void, -1> {
		using Type = _DeserialisableType<T, true, -1, TypeInArray, is_nullable<TypeInArray>::value, typename is_nullable<TypeInArray>::Type, -1>;
	};

	template<typename T, typename TypeInArray>
	struct _Deserialisable<T, true, -1, TypeInArray, false, void, -1> {
		using Type = _DeserialisableType<T, true, -1, TypeInArray, false, void, is_string<TypeInArray>::value>;
	};

    template<typename T, typename TypeInArray, typename TypeInNullable>
    struct _Deserialisable<T, true, -1, TypeInArray, true, TypeInNullable, -1> {
        using Type = _DeserialisableType<T, true, -1, TypeInArray, true, TypeInNullable, is_string<TypeInNullable>::value>;
    };

    template<typename StringType>
    struct _Deserialisable<StringType, false, -1, void, false, void, true> {
        using Type = String<StringType>;
    };

	template<typename T, typename StringType>
	struct _Deserialisable<T, false, -1, void, true, StringType, true> {
		using Type = NullableString<T, StringType>;
	};

	template<typename T, typename TypeInNullable>
	struct _Deserialisable<T, false, -1, void, true, TypeInNullable, false> {
		using Type = Nullable<T, TypeInNullable>;
	};

	template<typename T>
	struct Deserialisable<std::vector<T>> {
		using Type = _DeserialisableType<std::vector<T>, true, -1, T>;
	};

	template<typename T>
	struct Deserialisable<QList<T>> {
		using Type = _DeserialisableType<QList<T>, true, -1, T>;
	};

	template<typename T>
	struct Deserialisable<std::list<T>> {
		using Type = _DeserialisableType<std::list<T>, true, -1, T>;
	};

	template<typename T>
	struct Deserialisable<std::set<T>> {
		using Type = _DeserialisableType<std::set<T>, true, -1, T>;
	};

	template<typename T>
	struct Deserialisable<QSet<T>> {
		using Type = _DeserialisableType<QSet<T>, true, -1, T>;
	};

	template<typename TypeInArray, int N>
	struct Deserialisable<TypeInArray[N]> {
		using Type = _DeserialisableType<TypeInArray[N], true, N, TypeInArray>;
	};

	template<typename TypeInArray, int N>
	struct Deserialisable <std::array<TypeInArray, N>> {
		using Type = _DeserialisableType<std::array<TypeInArray, N>, true, N, TypeInArray>;
	};

	template<typename T, typename StringType>
	struct _Deserialisable<T, true, -1, StringType, false, void, true> {
		using Type = StringArray<T, StringType>;
	};

	template<typename T, typename Nullable, typename StringType>
	struct _Deserialisable<T, true, -1, Nullable, true, StringType, true> {
		using Type = NullableStringArray<T, Nullable, StringType>;
	};

	template<typename ArrayType, typename T>
	struct _Deserialisable<ArrayType, true, -1, T, false, void, false> {
		using Type = Array<ArrayType, T>;
	};

	template<typename T, typename StringType, int N>
	struct _Deserialisable<T, true, N, StringType, false, void, true> {
		using Type = LimitedStringArray<T, StringType, N>;
	};

	template<typename T, typename Nullable, typename StringType, int N>
	struct _Deserialisable<T, true, N, Nullable, true, StringType, true> {
		using Type = LimitedNullableStringArray<T, Nullable, StringType, N>;
	};

	template<typename Key, typename Value>
	struct Deserialisable<std::map<Key, Value>> {
		using Type = MapArray<std::map<Key, Value>, Key, Value>;
	};

	template<typename Key, typename Value>
	struct Deserialisable<QMap<Key, Value>> {
		using Type = MapArray<QMap<Key, Value>, Key, Value>;
	};

	template<typename First, typename Second>
	struct Deserialisable<std::pair<First, Second>> {
		using Type = Pair<std::pair<First, Second>, First, Second>;
	};

    template<>
    struct Deserialisable<QJsonValue> {
        using Type = JSONWrap;
    };

	template<>
	struct Deserialisable<bool> {
		using Type = Boolean;
	};

	template<>
	struct Deserialisable<int> {
		using Type = Integer<int>;
	};

	template<>
	struct Deserialisable<unsigned> {
		using Type = Integer<unsigned, false>;
	};

	template<>
	struct Deserialisable<double> {
		using Type = Real<double>;
	};
	
	template<size_t length>
	struct Deserialisable<char[length]> {
		using Type = String<char[length], length>;
	};

	template<>
	struct Deserialisable<const char*> {
		using Type = String<char*>;
	};

	template<>
	struct Deserialisable<const wchar_t*> {
		using Type = String<wchar_t*>;
	};
}

#define declare_top_deserialiser(data_name, var_name) JsonDeserialise::DeserialisableType<decltype(data_name)> var_name((data_name));
#define declare_deserialiser(json_name, data_name, var_name) JsonDeserialise::DeserialisableType<decltype(data_name)> var_name((json_name), (data_name));
#define declare_extension_deserialiser(json_name, data_name, var_name, convertor, deconvertor) JsonDeserialise::Extension var_name(JsonDeserialise::Convertor<decltype(data_name), decltype(convertor), decltype(deconvertor)>((convertor), (deconvertor)), json_name, data_name);
#define declare_one_direction_extension_deserialiser(json_name, data_name, var_name, convertor) JsonDeserialise::OneDirectionExtension var_name(JsonDeserialise::OneDirectionConvertor<decltype(data_name), decltype(convertor)>((convertor)), json_name, data_name);
#define declare_simple_map_deserialiser(data_name, key_name, val_name, var_name) JsonDeserialise::DeserialisableType<decltype(data_name)> var_name(data_name, key_name, val_name);
#define declare_object_map_deserialiser(data_name, key_name, var_name) JsonDeserialise::DeserialisableType<decltype(data_name)> var_name(data_name, key_name);
#define declare_pair_deserialiser(object_name, json_name1, json_name2, data_name, var_name) JsonDeserialise::DeserialisableType<decltype(data_name)> var_name((object_name), (data_name), (json_name1), (json_name2));
#define declare_pair_array_deserialiser(json_name1, json_name2, data_name, var_name) JsonDeserialise::DeserialisableType<decltype(data_name)> var_name((data_name), (json_name1), (json_name2));
#define declare_serialiser(json_name, data_name, var_name) const JsonDeserialise::DeserialisableType<decltype(data_name)> var_name((json_name), const_cast<std::decay_t<decltype(data_name)>&>(data_name));
#define declare_top_serialiser(data_name, var_name) const JsonDeserialise::DeserialisableType<decltype(data_name)> var_name(const_cast<std::decay_t<decltype(data_name)>&>(data_name));
#define declare_object_deserialiser(json_name, object_type, var_name, ...) JsonDeserialise::Object var_name(QStringLiteral(json_name), (object_type*)(nullptr), __VA_ARGS__);
#define array_object_member(object_type, json_name, member_name) JsonDeserialise::Info(json_name, &((object_type*)nullptr)->member_name)
#define declare_object_array(object_type, data_name, var_name, ...) JsonDeserialise::ObjectArray var_name(data_name, (object_type*)nullptr, __VA_ARGS__);
#define declare_non_trivial_as(type_name, as) template<> struct JsonDeserialise::Deserialisable<type_name> { using Type = JsonDeserialise::NonTrivial<type_name, as>; };
#define register_object_member(object_type, json_name, member_name) namespace JsonDeserialise {const char object_type##_##member_name[] = json_name;};
#define object_member(object_type, member_name) JsonDeserialise::ReinforcedInfo<decltype(((object_type*)nullptr)->member_name), JsonDeserialise::object_type##_##member_name, (offsetof(object_type, member_name))>
#define declare_object(object_type, ...) template<> struct JsonDeserialise::Deserialisable<object_type> { using Type = DeserialisableObject<object_type, __VA_ARGS__>; };
#define declare_class_with_json_constructor_and_serialiser(object_type) template<> struct JsonDeserialise::Deserialisable<object_type> { using Type = SelfDeserialisableObject<object_type>; };
#define register_map_with_key(container_type, key_type, value_type, key_name) namespace JsonDeserialise { const char key_type##_##map_type##_##key_json_name[] = key_name; template<> struct Deserialisable<container_type<key_type, value_type>> { using Type = MapArray<container_type<key_type, value_type>, key_type, value_type, key_type##_##map_type##_##key_json_name>; };}
#define declare_object_with_base_class(object_type, base_type, ...) template<> struct JsonDeserialise::Deserialisable<object_type> { using Type = DerivedObject<base_type, object_type, __VA_ARGS__>; };

#endif // JSON_DESERIALISER_H
